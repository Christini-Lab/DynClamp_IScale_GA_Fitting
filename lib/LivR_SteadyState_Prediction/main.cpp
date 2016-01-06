/*** INTRO
 *
 * LivR_SS_Prediction testing main.cpp
 * main.cpp
 *
 * Predictions the steady-state conditions of the model based on conductance
 * scaling parameters.
 *
 ***/

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "LivR_SS_Prediction.hpp"

int main(int argc, char *argv[]) {
  // Arguments: 13 scaling parameters
  if (argc != 14) {
    std::cout << "Error: invalid number of arguments: " << argc <<
        " instead of 14" << std::endl;
    exit(EXIT_FAILURE);
  }
  // Retrieve parameter scalings from command line arguments
  std::vector<double> g(13);
  for (int i = 0; i < 13; i++) {
    std::istringstream ss(argv[i + 1]);
    if (!(ss >> g.at(i))) {
      std::cout << "Error: invalid parameter argument, must be a number" <<
          std::endl;
      exit(EXIT_FAILURE);
    }
  }

  LivR_SS_Prediction LivR_IntialConditions;

  std::cout << "Livshitz Rudy 2009 steady-state predictions using nominal "
            << "parameters (i.e. conductance scalings of 1.0)." << std::endl;

  // Order of arguments:
  // GNa, GNab, GCaL, GCaT, GCab, GK1, GKr, GKs, GKp, INaK, kNCX, GpCa, Gserca
  std::cout << std::setprecision(12);
  std::cout << "Nai: " <<
      LivR_IntialConditions.predict_Nai(
          g.at(0), g.at(1), g.at(2), g.at(3), g.at(4), g.at(5), g.at(6),
          g.at(7), g.at(8), g.at(9), g.at(10), g.at(11), g.at(12)
                                        )
            << std::endl;
  std::cout << "Ki: " <<
      LivR_IntialConditions.predict_Ki(
          g.at(0), g.at(1), g.at(2), g.at(3), g.at(4), g.at(5), g.at(6),
          g.at(7), g.at(8), g.at(9), g.at(10), g.at(11), g.at(12)
                                        )
            << std::endl;
  std::cout << "Cai: " <<
      LivR_IntialConditions.predict_Cai(
          g.at(0), g.at(1), g.at(2), g.at(3), g.at(4), g.at(5), g.at(6),
          g.at(7), g.at(8), g.at(9), g.at(10), g.at(11), g.at(12)
                                        )
            << std::endl;
  std::cout << "CaJSR: " <<
      LivR_IntialConditions.predict_CaJSR(
          g.at(0), g.at(1), g.at(2), g.at(3), g.at(4), g.at(5), g.at(6),
          g.at(7), g.at(8), g.at(9), g.at(10), g.at(11), g.at(12)
                                        )
            << std::endl;
  std::cout << "CaNSR: " <<
      LivR_IntialConditions.predict_CaNSR(
          g.at(0), g.at(1), g.at(2), g.at(3), g.at(4), g.at(5), g.at(6),
          g.at(7), g.at(8), g.at(9), g.at(10), g.at(11), g.at(12)
                                        )
            << std::endl;
}
