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
There are minor differences between the 10kHz simulation, 100kHz simulation, and
the dynamic clamp data. Interestingly, while the 10kHz simulation has an
expected mismatch during the upstroke due to the slower integration rate, the
100kHz simulation has overall a slightly higher error.

### Conclusions
Since the differences between the 10kHz and 100kHz simulation are neglible,
however, when trying to integrate the model at 10kHz, the model is unstable when
scaling parameters. So in the end, 100kHz integration will be used.

The 100kHz simulation data is used as the simulation objective when fitting the
model to itself.