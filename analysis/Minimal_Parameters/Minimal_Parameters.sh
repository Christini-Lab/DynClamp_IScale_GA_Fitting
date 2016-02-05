#!/bin/bash
EXEC=./Minimal_GA_Fitting
OBJECTIVE=../../objectives/Objective_GA_Protocol_Simulation.dat
PROTOCOL=../../protocols/Protocol_DynClamp_Simulation.dat
FOLDERNAME=Minimal_GA_Protocol

# Loop through objectives and protocols
SETTINGS="settings.ga"

# Run GA 10 times with nominal bounds
for ((z = 0; z < 5; z++)); do
    echo $EXEC $OBJECTIVE $PROTOCOL $SETTINGS
done

# Find new bounds based on last 10 Runs
Rscript Set_New_Bounds.R new_bounds.ga *.dat

# Move first 5 runs into another directory
if [ ! -d "Standard_Bounds" ]; then
    mkdir Standard_Bounds
fi
mv *.dat Standard_Bounds

SETTINGS="new_bounds.ga"

# Run GA 5 times with new bounds
for ((z = 0; z < 5; z++)); do
    echo $EXEC $OBJECTIVE $PROTOCOL $SETTINGS
done

# Move second set of 10 runs into another directory
if [ ! -d "Constrained_Bounds" ]; then
    mkdir Constrained_Bounds
fi
mv *.dat Constrained_Bounds

# Move run data into another directory
if [ ! -d "Data/$FOLDERNAME" ]; then
    mkdir -p Data/$FOLDERNAME
fi
mv Standard_Bounds Constrained_Bounds Data/$FOLDERNAME
