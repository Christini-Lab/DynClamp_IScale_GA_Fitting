# Fitting to Nominal Model
---

### Introduction
In this set of fitting runs, the GA will attempt to fit the model to itself with
its nominal parameters. The initial 10 GA runs use an initial bounds of 0.001%
to 300% scaling. A second set of 10 GA runs are then run, with constrained
parameter bounds based on the best individuals from each of the first 10 runs.
The bounds are the span of each parameter across the 10 best individuals. Since
the GA is attempting to fit to the nominal model, we know the ideal error to be
~0 and the ideal parameter set to consist of 100% scalings.