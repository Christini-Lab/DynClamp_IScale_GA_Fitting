#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Genetic Algorithm
#include "../../lib/Genetic_Algorithm/include/main_ga.hpp"
#include "../../lib/Genetic_Algorithm/include/random.hpp"
#include "../../lib/Genetic_Algorithm/include/globalSetup.hpp"

// Livshitz Rudy 2009 Model
#include "../../lib/LivRudy2009/include/LivRudy2009.hpp"
#include "../../lib/LivR_SteadyState_Prediction/LivR_SS_Prediction.hpp"

// Global variables
GlobalSetup *globalSetup;
Random myRandom;
std::vector< std::vector<double> > objectiveTraces; // Acquired at 10 kHz
std::vector< std::vector<double> > protocolTraces; // Acquired at 10 kHz

#define PROTOCOLDT 0.1 // (ms) Time step of protocol data
#define MINDT 0.001 // (ms) minimum dt, 1000 kHz integration
#define MAXDT 0.1 // (ms) maximum dt, 10kHz integration, should be <= PROTOCOLDT

// Model simulation and objective evaluation
void globalEvaluate(double *parameter, double *error,
                    double *constraintViolation, double *penalty,
                    int *noOfViolations) {
  LivRudy2009 model;

  // Each thread will make a copy of objectives and protocols. While this does
  // have an overhead, it is neglible compared to running the simulation and
  // makes the code cleaner while protecting the shared variable.
  std::vector< std::vector<double> > objectives, protocols;
#pragma omp critical
  {
    objectives = objectiveTraces;
    protocols = protocolTraces;
  }

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

  //Predict and set initial concentrations
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

  double dt = MAXDT; // Adaptive timestep, starting at max
  double dVdt; // dVdt is used to modify timestep
  const double dVdtThresh = MAXDT * 2; // If dVdt is less than this, reduce dt
  double v0 = model.getVm(); // Voltage of previous timestep to calculate dVdt
  int steps = dt / PROTOCOLDT; // Number of integration steps
  const int maxSteps = PROTOCOLDT / MINDT; // Max number of integration steps
  // Static pacing beats before each perturbation to elminate transients
  int numPrelimBeats = 25;
  int numPerturbBeats = 5;
  double cm = protocols.back().at(0) * 1e-12;
  protocols.resize(protocols.size() - 1); // Remove cm once extracted

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
        dt = MAXDT;
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

  double totalError = 0;

  // Run voltage protocol
  // Skip static pacing, only voltage clamp error will be used for fitting
  // dVdt changed to calculate dIdt
  for (int i = 1; i < protocols.size(); i++) {
    // Set of 5 runs are summated
    // Initialize vector for voltage summation
    std::vector<double> vmData(protocols.at(i).size(), 0.0);
    for (int z = 0; z < numPerturbBeats; z++) {
      auto it = protocols.at(i).begin();
      auto ot = vmData.begin();
      // Extract current from protocol and scale by cm each loop
      // Loop will exit if model crashes
      double v0 = model.getI(); // Get initial current for dVdt evaluation

      // Steps through each step of the protocol and inject current
      while (it != protocols.at(i).end()) {
        dVdt = std::abs(model.getI() - v0) / PROTOCOLDT;
        v0 = model.getI();

        // Adaptive dt calculation
        // Voltage is changing less than threshold, so use max dt
        if (dVdt < dVdtThresh) {
          dt = MAXDT;
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
        while (idx < steps && model.vClamp(*it)) {
          idx++;
        }

        if (model.getStatus()) {
          *ot += model.getI(); // Save running sum of current
          it++; // Increment to next protocol step if model did not crash
          ot++;
        }
        else
          break; // if model crashed, exit loop
      }
    }

    // Divide by number of beats for average
    std::transform(vmData.begin(), vmData.end(), vmData.begin(),
                   [=] (double sumVm) {
                     return sumVm / numPerturbBeats;
                   });

    // Calculate difference between average voltage and objective and
    // save to vmData vector.
    std::transform(vmData.begin(), vmData.end(),
                   objectives.at(i).begin(),
                   vmData.begin(),
                   [] (double modelVm, double objectiveVm) {
                     return std::abs(modelVm - objectiveVm);
                   });
    // Perform normal error calculation
    // Calculate total error
    totalError += std::accumulate(vmData.begin(),
                                  vmData.end(),
                                  0.0);
  }
    // If model crashed, set error to arbitrarily high value
    if (!model.getStatus()) {
      error[0] = 400 * 60000;
    }
    else {
      error[0] = totalError;
    }

#pragma omp ordered
  {
    if (globalSetup->savePopulation) {
      FILE *outEvals = fopen(globalSetup->saveEvalSolutions, "a");
      for (int i = 0; i < globalSetup->noOfDecisionVariables; i++) {
        fprintf(outEvals, "%f\t", parameter[i]);
      }
      for (int i = 0; i < globalSetup->finalNoOfObjectives; i++) {
        fprintf(outEvals, "%f\t", error[i]);
      }
      if (globalSetup->finalNoOfConstraints > 0) {
        for (int i = 0; i < globalSetup->finalNoOfConstraints; i++) {
          fprintf(outEvals, "%f\t", constraintViolation[i]);
        }
        fprintf(outEvals, "%f", *penalty);
      }
      fprintf(outEvals, "\n");
      fflush(outEvals);
      fclose(outEvals);
    }
  }
}

int main(int argc, char *argv[]) {
  // Input objective and protocol traces from data files
  std::string line;
  // Objective
  std::ifstream objFile(argv[1]);
  if (!objFile.good()) {
    std::cout << "Error: unable to open objective file" << std::endl;
    exit(1);
  }
  while (std::getline(objFile, line, '\n')) {
    std::vector<double> lineData;
    std::stringstream lineStream(line);
    double value;

    while (lineStream >> value)
      lineData.push_back(value);

    objectiveTraces.push_back(lineData);
  }
  // Protocol
  std::ifstream proFile(argv[2]);
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

    protocolTraces.push_back(lineData);
  }

  // Double check protocol and objective matrixes match desired dimensions
  // Protocol should have one extra row, since it contains membrane capacitance
  if (protocolTraces.size() - 1 != objectiveTraces.size()) {
    std::cout <<
        "Error: Protocol and objective sizes do not match" << std::endl <<
        "Protocol size - 1: " << protocolTraces.size() - 1 << std::endl <<
        "Protocol file: " << argv[1] << std::endl <<
        "Objective size: " << objectiveTraces.size() << std::endl <<
        "Objective file: " << argv[2] << std::endl;
    exit(0);
  }
  run_GA(argv[3]);

  return EXIT_SUCCESS;
}
