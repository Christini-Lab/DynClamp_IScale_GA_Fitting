# GA evaluation versus dynamic clamp simulation
---

### Introduction
Two simulations were performed, the much longer simulation using the
experimental RTXI rig to perform the same dynamic clamp experiment done on
guinea pig ventricular myocytes, but instead on the Livshitz Rudy 2009 model.
The second simulation is identical to the one performed on each individual
within the genetic algorithm. This analysis compares the differences between two
simulations.

### Results
The differences between the 10kHz model, 100kHz model, and dynamic clamp
are neglible, but do exist. Interestingly, while the dynamic clamp simulation
was done using a model running at a 100kHz, the 10kHz model had a lower error
(1008 mV versus 1633 mV over 5000 data points).

### Notes
  * The 10kHz simulation is saved as an objective.
  * The R plotting script can be run within an IDE or through the command line
    using Rscript
    ```sh
    Rscript Plot_Comparison.R
    ```