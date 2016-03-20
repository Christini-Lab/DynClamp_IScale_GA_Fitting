#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iterator>

#define NUMPARAM 13 // Number of scaling parameters
#define PROTOCOLDT 0.1 // (ms) Time step of protocol data
#define MINDT 0.001 // (ms) minimum dt, 1000 kHz integration

// Livshitz Rudy 2009 Model
#include "../../lib/LivRudy2009/include/LivRudy2009.hpp"
#include "../../lib/LivR_SteadyState_Prediction/LivR_SS_Prediction.hpp"

int main(int argc, char *argv[]) {
  // Arguments: Scaling parameters, dt, objective, protocol file, voltage output
  // file, error output file
  if (argc != (NUMPARAM + 6)) {
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

  // Retrieve maximum dt for adaptive timestep
  std::istringstream dt_ss(argv[NUMPARAM + 1]);
  double maxDt;
  if (!(dt_ss >> maxDt)) {
    std::cout << "Error: invalid dt, must be a number" <<
        std::endl;
    exit(EXIT_FAILURE);
  }

  // Retrieve objectives
  std::string line;
  std::vector< std::vector<double> > objectives; // Acquired at 10 kHz
  std::ifstream objFile(argv[NUMPARAM + 2]);
  if (!objFile.good()) {
    std::cout << "Error: unable to open objectives file" << std::endl;
    exit(1);
  }
  while (std::getline(objFile, line, '\n')) {
    std::vector<double> lineData;
    std::stringstream lineStream(line);
    double value;

    while (lineStream >> value)
      lineData.push_back(value);

    objectives.push_back(lineData);
  }


  // Retrieve protocol
  std::vector< std::vector<double> > protocols; // Acquired at 10 kHz
  std::ifstream proFile(argv[NUMPARAM + 3]);
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
  double totalError = 0;

  // Scale model parameters
  model.setGNa(model.getGNa() * parameter[0]);
  model.setGNab(model.getGNab() * parameter[1]);
  model.setGCaL(model.getGCaL() * parameter[2]);
  model.setGCaT(model.getGCaT() * parameter[3]);
  model.setGCab(model.getGCab() * parameter[4]);
  model.setGK1(model.getGK1() * parameter[5]);
  model.setGKr(model.getGKr() * parameter[6]);
  model.setGKs(model.getGKs() * parameter[7]);
  model.setGKp(model.getGKp() * parameter[8]);
  model.setGNaK(model.getGNaK() * parameter[9]);
  model.setGNCX(model.getGNCX() * parameter[10]);
  model.setGpCa(model.getGpCa() * parameter[11]);
  model.setGserca(model.getGserca() * parameter[12]);

  // Predict and set initial concentrations
  LivR_SS_Prediction intialConcentrations;
  model.setNai(
      intialConcentrations.predict_Nai(
          parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
          parameter[5], parameter[6], parameter[7], parameter[8], parameter[9],
          parameter[10], parameter[11], parameter[12]));
  model.setKi(
      intialConcentrations.predict_Ki(
          parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
          parameter[5], parameter[6], parameter[7], parameter[8], parameter[9],
          parameter[10], parameter[11], parameter[12]));
  model.setCai(
      intialConcentrations.predict_Cai(
          parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
          parameter[5], parameter[6], parameter[7], parameter[8], parameter[9],
          parameter[10], parameter[11], parameter[12]));
  model.setCaJSR(
      intialConcentrations.predict_CaJSR(
          parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
          parameter[5], parameter[6], parameter[7], parameter[8], parameter[9],
          parameter[10], parameter[11], parameter[12]));
  model.setCaNSR(
      intialConcentrations.predict_CaNSR(
          parameter[0], parameter[1], parameter[2], parameter[3], parameter[4],
          parameter[5], parameter[6], parameter[7], parameter[8], parameter[9],
          parameter[10], parameter[11], parameter[12]));

  double dt = maxDt; // Adaptive timestep, starting at max
  double dVdt; // dVdt is used to modify timestep
  const double dVdtThresh = maxDt * 2; // If dVdt is less than this, reduce dt
  double v0 = model.getVm(); // Voltage of previous timestep to calculate dVdt
  int steps = dt / PROTOCOLDT; // Number of integration steps
  const int maxSteps = PROTOCOLDT / MINDT; // Max number of integration steps
  // Static pacing beats before each perturbation to elminate transients
  int numPrelimBeats = 1000;
  int numPerturbBeats = 5;
  double cm = protocols.back().at(0) * 1e-12;
  protocols.resize(protocols.size() - 1); // Remove cm once extracted

  std::vector< std::vector<double> >
      runData(protocols.size(),
              std::vector<double>(protocols.at(0).size()));

  // Vector for voltage differences between simulation and objective
  std::vector< std::vector<double> >
      vmDiff(protocols.size(),
             std::vector<double>(protocols.at(0).size()));

  // Static pacing, using static pacing current
  // Conditions are saved, and model is set to those initial conditions before
  // each perturbation.
  for (int z = 0; z < numPrelimBeats; z++) {
    auto it = protocols.at(0).begin();
    // Extract current from protocol and scale by cm each loop
    // Loop will exit if model crashes
    double v0 = model.getVm(); // Get initial voltage for dVdt evaluation

    // Steps through each step of the protocol and inject current
    while (it != protocols.at(0).end()) {
      dVdt = std::abs(model.getVm() - v0) / PROTOCOLDT;
      v0 = model.getVm();
      // Adaptive dt calculation
      // Voltage is changing less than threshold, so use max dt
      if (dVdt < dVdtThresh) {
        dt = maxDt;
        model.setDt(dt);
        steps = PROTOCOLDT / dt;
      }
      else { // Voltage is changing quickly, so reduce dt up to minimum
        steps = std::ceil(dVdt / dVdtThresh); // Round up to an integer

        if (steps > maxSteps)
          steps = maxSteps;

        dt = PROTOCOLDT / steps;
        model.setDt(dt);
      }

      int idx = 0;
      // Integrate using adaptive dt, loop breaks if model crashes
      while (idx < steps && model.iClamp(*it / cm * -1)) {
        idx++;
      }

      if (model.getStatus())
        it++; // Increment to next protocol step if model did not crash
      else
        break; // if model crashed, exit loop
    }
  }

  std::vector<double> conditions(model.getConditions());

  // Run each proocol
  for (int i = 0; i < protocols.size(); i++) {
    // Set conditions to after static pacing beats
    model.setConditions(conditions);

    // Current perturbation for 10 beats
    // First set of 5 beats are not recorded
    for (int z = 0; z < numPerturbBeats; z++) {
      auto it = protocols.at(i).begin();
      // Extract current from protocol and scale by cm each loop
      // Loop will exit if model crashes
      double v0 = model.getVm(); // Get initial voltage for dVdt evaluation

      // Steps through each step of the protocol and inject current
      while (it != protocols.at(i).end()) {
        dVdt = std::abs(model.getVm() - v0) / PROTOCOLDT;
        v0 = model.getVm();

        // Adaptive dt calculation
        // Voltage is changing less than threshold, so use max dt
        if (dVdt < dVdtThresh) {
          dt = maxDt;
          model.setDt(dt);
          steps = PROTOCOLDT / dt;
        }
        else { // Voltage is changing quickly, so reduce dt up to minimum
          steps = std::ceil(dVdt / dVdtThresh); // Round up to an integer

          if (steps > maxSteps)
            steps = maxSteps;

          dt = PROTOCOLDT / steps;
          model.setDt(dt);
        }
        int idx = 0;

        // Integrate using adaptive dt, loop breaks if model crashes
        while (idx < steps && model.iClamp(*it / cm * -1)) {
          idx++;
        }

        if (model.getStatus())
          it++; // Increment to next protocol step if model did not crash
        else
          break; // if model crashed, exit loop
      }
    }

    // Second set of 5 beats are summated
    // Initialize vector for voltage summation
    std::vector<double> vmData(protocols.at(i).size(), 0.0);
    for (int z = 0; z < numPerturbBeats; z++) {
      auto it = protocols.at(i).begin();
      auto ot = vmData.begin();
      // Extract current from protocol and scale by cm each loop
      // Loop will exit if model crashes
      double v0 = model.getVm(); // Get initial voltage for dVdt evaluation

      // Steps through each step of the protocol and inject current
      while (it != protocols.at(i).end()) {
        dVdt = std::abs(model.getVm() - v0) / PROTOCOLDT;
        v0 = model.getVm();

        // Adaptive dt calculation
        // Voltage is changing less than threshold, so use max dt
        if (dVdt < dVdtThresh) {
          dt = maxDt;
          model.setDt(dt);
          steps = PROTOCOLDT / dt;
        }
        else { // Voltage is changing quickly, so reduce dt up to minimum
          steps = std::ceil(dVdt / dVdtThresh); // Round up to an integer

          if (steps > maxSteps)
            steps = maxSteps;

          dt = PROTOCOLDT / steps;
          model.setDt(dt);
        }

        int idx = 0;

        // Integrate using adaptive dt, loop breaks if model crashes
        while (idx < steps && model.iClamp(*it / cm * -1)) {
          idx++;
        }

        if (model.getStatus()) {
          *ot += model.getVm(); // Save running sum of voltage
          it++; // Increment to next protocol step if model did not crash
          ot++;
        }
        else
          break; // if model crashed, exit loop
      }
    }

    if (!model.getStatus()) {
      std::cout << "ERROR: Model crash" << std::endl;
      return 0;
    }

    // Divide by number of beats for average
    std::transform(vmData.begin(), vmData.end(), vmData.begin(),
                   [=] (double sumVm) {
                     return sumVm / numPerturbBeats;
                   });

    // Calculate difference between average voltage and objective and
    // save to vmDiff vector.
    std::transform(vmData.begin(), vmData.end(),
                   objectives.at(i).begin(),
                   vmDiff.at(i).begin(),
                   [] (double modelVm, double objectiveVm) {
                     return std::abs(modelVm - objectiveVm);
                   });


    // Calculate total error
    std::for_each(vmDiff.begin(), vmDiff.end(),
                  // Summate differences between simulation and objective
                  // and add to total error
                  [&totalError] (std::vector<double> simVsObj) {
                    totalError += std::accumulate(simVsObj.begin(),
                                                  simVsObj.end(),
                                                  0.0);
                  });

    std::cout << "Vm Data: " <<
        "Max: " << *std::max_element(vmData.begin(), vmData.end()) <<
        " | Min: " << *std::min_element(vmData.begin(), vmData.end()) <<
        std::endl;

    runData.at(i) = vmData;
  }

  // Output voltage data
  std::ofstream dataFile(argv[NUMPARAM + 4]);
  dataFile << std::setprecision(8);
  for (auto it = runData.begin(); it != runData.end(); it++) {
    std::copy((*it).begin(), (*it).end(),
              std::ostream_iterator<double>(dataFile, " "));
    dataFile << std::endl;
  }

  std::cout << "Error: " << totalError << std::endl;
  std::ofstream errorFile(argv[NUMPARAM + 5]);
  errorFile << std::setprecision(8);
  errorFile << totalError;

  return EXIT_SUCCESS;
}
