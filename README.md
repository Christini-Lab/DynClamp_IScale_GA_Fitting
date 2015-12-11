# Model fitting using experimental dynamic clamp perturbations

### Introduction
Experimental measurements from guinea pig ventricular myocytes of dynamic clamp
perturbations are used to fit the behavior of the Livshitz Rudy 2009 ventricular
model. Contains experimental data from 14 cells (Cell_1 - Cell_14) as well as
the Livshitz Rudy 2009 model itself (Cell_15).


### Protocol files
These files contain the cell membrane capacitance and injected current of the
dynamic clamp experiment. The files are organized by row:
  1. Pacing current injection
  2. IKr current injection
  3. IKs current injection
  4. ICaL current injection
  5. IK1 current injection
  6. ICaT current injection
  7. INaK current injection
  8. INCX current injection
  9. Cell membrane capacitance


### Objective files
These files contain cell membrane voltage during each dynamic clamp
perturbation. The files are organized by row:
  1. Static pacing membrane voltage response
  2. IKr - membrane voltage response
  3. IKs - membrane voltage response
  4. ICaL - membrane voltage response
  5. IK1 - membrane voltage response
  6. ICaT - membrane voltage response
  7. INaK - membrane voltage response
  8. INCX - membrane voltage response


### Libraries
A genetic algorithm and the Livshitz Rudy 2009 model used in the dynamic clamp
experiments have been added to this repository as subtrees. If you wish to
update the libraries, you must first add the remote repository and merge in any
new changes.


### Execution scripts
Located in the execution/ directory.

  * **Nominal_Model_Fitting** - The genetic algorithm is used to fit the model
  to objective data created using the nominal parameters of the model. In short,
  the ideal fit has an error is ~0 with all parameters set to 1.0.

### Analysis scripts
Located in the analysis/ directory.

### Running the fitting
The fitting executable requires 3 arguments:
  * Objective file
  * Protocol file
  * Genetic algorithm settings file

An example command to fit the model to nominal parameters is as follows:
```sh
make && ./GA_Fitting objectives/Objective_GA_Protocol_Simulation.dat protocols/Protocol_DynClamp_Simulation.dat settings.ga
```