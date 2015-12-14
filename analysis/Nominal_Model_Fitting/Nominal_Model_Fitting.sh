#!/bin/bash
EXEC="../../GA_Fitting"
OBJECTIVE="../../objectives/Objective_GA_Protocol_Simulation.dat"
PROTOCOL="../../protocols/Protocol_DynClamp_Simulation.dat"
SETTINGS="../../settings.ga"

# Run GA 10 times with nominal bounds
for i in `seq 1 10`;
do
    $EXEC $OBJECTIVE $PROTOCOL $SETTINGS
done

# Find new bounds based on last 10 Runs
Rscript Set_New_Bounds.R new_bounds.ga *.dat

# Move first 10 runs into another directory
if [ ! -d "Standard_Bounds" ]; then
  mkdir Standard_Bounds
fi
mv *.dat Standard_Bounds

SETTINGS="new_bounds.ga"

# Run GA 10 times with new bounds
for i in `seq 1 10`;
do
    $EXEC $OBJECTIVE $PROTOCOL $SETTINGS
done

# Move second set of 10 runs into another directory
if [ ! -d "Constrained_Bounds" ]; then
  mkdir Constrained_Bounds
fi
mv *.dat Constrained_Bounds
