#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iterator>

#define NUMPARAM 11 // Number of scaling parameters

// Livshitz Rudy 2009 Model
#include "../../lib/LivRudy2009/include/LivRudy2009.hpp"

int main(int argc, char *argv[]) {
  // Arguments: Scaling parameters, dt, protocol file, voltage output file
  if (argc != (NUMPARAM + 4)) {
    std::cout << "Error: invalid number of arguments: " << argc <<
        " instead of " << NUMPARAM + 4 << std::endl;
    exit(EXIT_FAILURE);
  }
  // Retrieve parameter scalings from command line arguments
  std::vector<double> parameter(NUMPARAM);
  for (int i = 0; i < NUMPARAM; i++) {
    std::istringstream ss(argv[i + 1]);
    if (!(ss >> parameter.at(i))) {
      std::cout << "Error: invalid parameter argument, must be a number" <<
          std::endl;
      exit(EXIT_FAILURE);
    }
  }

  // Retrieve dt
  std::istringstream dt_ss(argv[NUMPARAM + 1]);
  double dt;
  if (!(dt_ss >> dt)) {
    std::cout << "Error: invalid dt, must be a number" <<
        std::endl;
    exit(EXIT_FAILURE);
  }

  // Retrieve protocol
  std::string line;
  std::vector< std::vector<double> > protocols; // Acquired at 10 kHz
  std::ifstream proFile(argv[NUMPARAM + 2]);
  if (!proFile.good()) {
    std::cout << "Error: unable to open protocol file" << std::endl;
    exit(1);
  }
  while (std::getline(proFile, line, '\n')) {
    std::vector<double> lineData;
    std::stringstream lineStream(line);
    double value;

    while (lineStream >> value)
      lineData.push_back(value);

    protocols.push_back(lineData);
  }

  LivRudy2009 model;

  // Set parameters
  model.setGKr(model.getGKr() * parameter[0]);
  model.setGKs(model.getGKs() * parameter[1]);
  model.setGCaL(model.getGCaL() * parameter[2]);
  model.setGK1(model.getGK1() * parameter[3]);
  model.setGCaT(model.getGCaT() * parameter[4]);
  model.setGNaK(model.getGNaK() * parameter[5]);
  model.setGNCX(model.getGNCX() * parameter[6]);
  model.setGNa(model.getGNa() * parameter[7]);
  model.setGKp(model.getGKp() * parameter[8]);
  model.setGpCa(model.getGpCa() * parameter[9]);
  model.setGserca(model.getGserca() * parameter[10]);

  // Data is acquired at 10 kHz
  model.setDt(dt);
  int steps = 0.1 / dt;

  // Static pacing beats before each perturbation to elminate transients
  int numPrelimBeats = 25;
  int numPerturbBeats = 5;
  double cm = protocols.back().at(0) * 1e-12;
  protocols.resize(protocols.size() - 1); // Remove cm once extracted

  // Vector for voltage differences between simulation and objective
  std::vector< std::vector<double> >
      vmDiff(protocols.size(),
             std::vector<double>(protocols.at(0).size()));

  // Static pacing, using static pacing current
  // Conditions are saved, and model is set to those initial conditions before
  // each perturbation.
  for (int z = 0; z < numPrelimBeats; z++) {
    auto it = protocols.at(0).begin();
    int cnt = 0;
    // Extract current from protocol and scale by cm each loop
    // Loop will exit if model crashes
    while (it != protocols.at(0).end() && model.iClamp(*it / cm * -1)) {
      cnt++;
      if (cnt % steps == 0)
        it++;
    }
  }

  std::vector<double> conditions(model.getConditions());

  // Run each protocol
  for (int i = 0; i < protocols.size(); i++) {
    // Set conditions to after static pacing beats
    model.setConditions(conditions);

    // Current perturbation for 10 beats
    // First set of 5 beats are not recorded
    for (int z = 0; z < numPerturbBeats; z++) {
      auto it = protocols.at(i).begin();
      int cnt = 0;
      // Extract current from protocol and scale by cm each loop
      // Loop will exit if model crashes
      while (it != protocols.at(i).end() && model.iClamp(*it / cm * -1)) {
        cnt++;
        if (cnt % steps == 0)
          it++;
      }
    }

    // Second set of 5 beats are summated
    // Initialize vector for voltage summation
    std::vector<double> vmData(protocols.at(i).size(), 0.0);
    for (int z = 0; z < numPerturbBeats; z++) {
      auto it = protocols.at(i).begin();
      auto ot = vmData.begin();
      int cnt = 0;
      while (it != protocols.at(i).end() && model.iClamp(*it / cm * -1)) {
        if (cnt % steps == 0) {
          // Running sum of the membrane voltage
          *ot += model.getVm();
          it++;
          ot++;
        }
        cnt++;
      }
    }

    // Divide by number of beats for average
    std::transform(vmData.begin(), vmData.end(), vmData.begin(),
                   [=] (double sumVm) {
                     return sumVm / numPerturbBeats;
                   });

    std::cout << "Vm Data: " <<
        "Max: " << *std::max_element(vmData.begin(), vmData.end()) <<
        " | Min: " << *std::min_element(vmData.begin(), vmData.end()) <<
        std::endl;

    runData.at(i) = vmData;
  }

  // Output voltage data
  std::ofstream dataFile(argv[NUMPARAM + 3]);
  dataFile << std::setprecision(8);
  for (auto it = runData.begin(); it != runData.end(); it++) {
    std::copy((*it).begin(), (*it).end(),
              std::ostream_iterator<double>(dataFile, " "));
    dataFile << std::endl;
  }
}
