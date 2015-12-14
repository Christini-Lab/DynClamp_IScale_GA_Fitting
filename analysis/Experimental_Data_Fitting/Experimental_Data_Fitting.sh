#!/bin/bash
EXEC="../../GA_Fitting"
OBJECTIVES=( \
    "../../objectives/Objective_Cell_2.dat" \
    "../../objectives/Objective_Cell_7.dat" \
    )
PROTOCOLS=( \
    "../../protocols/Protocol_Cell_2.dat" \
    "../../protocols/Protocol_Cell_7.dat" \
    )

# Loop through objectives and protocols
for ((i = 0; i < ${#OBJECTIVES[@]}; i++)); do
    SETTINGS="settings.ga"

    # Run GA 10 times with nominal bounds
    for ((z = 0; z < 10; z++)); do
        $EXEC ${OBJECTIVES[i]} ${PROTOCOLS[i]} $SETTINGS
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
    for ((z = 0; z < 10; z++)); do
        $EXEC ${OBJECTIVES[i]} ${PROTOCOLS[i]} $SETTINGS
    done

    # Move second set of 10 runs into another directory
    if [ ! -d "Constrained_Bounds" ]; then
        mkdir Constrained_Bounds
    fi
    mv *.dat Constrained_Bounds

    # Move run data into another directory
    if [ ! -d "Data/Run_$i" ]; then
        mkdir -p Data/Run_$i
    fi
    mv Standard_Bounds Constrained_Bounds Data/Run_$i
done
