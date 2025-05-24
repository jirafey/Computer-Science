#!/bin/bash

# --- Configuration ---
SIZES=(100 500 1000 2000) # Space-separated list of matrix sizes
THREADS=(2 4 8 16)         # Space-separated list of thread counts
# Schedules with chunk sizes
SCHEDULES_STATIC=("static,10" "static,50" "static,100")
SCHEDULES_DYNAMIC=("dynamic,10" "dynamic,50" "dynamic,100")
SCHEDULES_GUIDED=("guided,10" "guided,50" "guided,100")
ALL_SCHEDULES=("${SCHEDULES_STATIC[@]}" "${SCHEDULES_DYNAMIC[@]}" "${SCHEDULES_GUIDED[@]}") # Combine all

EXEC_BASE="matrix_multiply"
RESULTS_FILE="results.txt"

# --- Ensure executables exist ---
echo "Checking for executables..."
make # Run make to compile if needed
if [ ! -x "${EXEC_BASE}_l1" ] || [ ! -x "${EXEC_BASE}_l2" ] || [ ! -x "${EXEC_BASE}_l3" ]; then
    echo "Error: Executables not found or not executable. Please run 'make' first."
    exit 1
fi
echo "Executables found."

# --- Clear previous results ---
rm -f "$RESULTS_FILE"
echo "Cleared previous results file: $RESULTS_FILE"

# --- Run Experiments ---
echo "Starting experiments... Output will be saved to $RESULTS_FILE"

# Loop through each parallelization strategy (loop 1, 2, 3)
for loop_num in 1 2 3; do
    executable="${EXEC_BASE}_l${loop_num}"
    echo " " >> "$RESULTS_FILE" # Add spacing
    echo "--- Running Loop ${loop_num} Parallelization ---" | tee -a "$RESULTS_FILE" # Print header to file and screen

    # Loop through matrix sizes
    for size in "${SIZES[@]}"; do
        echo " " >> "$RESULTS_FILE"
        echo "--- Matrix Size: ${size} x ${size} ---" | tee -a "$RESULTS_FILE"

        # Loop through thread counts
        for threads in "${THREADS[@]}"; do
            echo "*** Threads: ${threads} ***" >> "$RESULTS_FILE"

            # Run with default schedule (OMP_SCHEDULE not set)
            echo "Schedule: Default (Static)" >> "$RESULTS_FILE"
            echo "Running: ./${executable} ${threads} ${size}"
            ./${executable} ${threads} ${size} >> "$RESULTS_FILE"
            if [ $? -ne 0 ]; then
                 echo "WARNING: Verification might have failed for Size=${size}, Threads=${threads}, Loop=${loop_num}, Schedule=Default" | tee -a "$RESULTS_FILE"
            fi


            # Run with specific schedules
            for sched in "${ALL_SCHEDULES[@]}"; do
                echo "Schedule: ${sched}" >> "$RESULTS_FILE"
                echo "Running: OMP_SCHEDULE=\"${sched}\" ./${executable} ${threads} ${size}"
                OMP_SCHEDULE="${sched}" ./${executable} ${threads} ${size} >> "$RESULTS_FILE"
                 if [ $? -ne 0 ]; then
                    echo "WARNING: Verification might have failed for Size=${size}, Threads=${threads}, Loop=${loop_num}, Schedule=${sched}" | tee -a "$RESULTS_FILE"
                 fi
            done # End schedules loop
        done # End threads loop
    done # End sizes loop
done # End loop_num loop

echo " "
echo "All experiments complete. Results saved in $RESULTS_FILE"

exit 0