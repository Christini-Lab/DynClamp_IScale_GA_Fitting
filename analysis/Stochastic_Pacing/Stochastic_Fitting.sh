#!/bin/bash
EXEC=./Stochastic_GA_Fitting
OBJECTIVE=Objective_Stochastic_Pacing.dat
PROTOCOL=Protocol_Stochastic_Pacing.dat
FOLDERNAME=Stochastic_Pacing

# Loop through objectives and protocols
SETTINGS="settings.ga"

# Run GA 10 times with nominal bounds
for ((z = 0; z < 5; z++)); do
    $EXEC $OBJECTIVE $PROTOCOL $SETTINGS 1>> $FOLDERNAME.log
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
    $EXEC $OBJECTIVE $PROTOCOL $SETTINGS 1>> $FOLDERNAME.log
done

# Move second set of 5 runs into another directory
if [ ! -d "Constrained_Bounds" ]; then
    mkdir Constrained_Bounds
fi
mv *.dat Constrained_Bounds

# Move all GA run data into data directory
if [ ! -d "Data/$FOLDERNAME" ]; then
    mkdir -p Data/$FOLDERNAME
fi
mv Standard_Bounds Constrained_Bounds Data/$FOLDERNAME

# Move settings file and log file into Data folder
mv new_bounds.ga $FOLDERNAME.log Data/$FOLDERNAME
