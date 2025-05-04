#!/bin/bash
set -euo pipefail

# sort_tester.sh - Sorting algorithm performance test script with improved features

# Configuration
ALGORITHMS=("quick" "quick-drunk-1" "quick-drunk-2" "quick-drunk-3" "quick-drunk-4" "quick-drunk-5" "insertion" "shell" "heap")
TYPES=("int" "float" "double" "char")
SIZES=(10000 20000 40000 80000 160000)
SORT_TYPES=("random" "ascending" "descending" "sorted33" "sorted66")
ITERATIONS=100

# Create results directory if it doesn't exist
mkdir -p results

# Check if main executable exists
if [ ! -f "./main" ] || [ ! -x "./main" ]; then
    echo "Error: './main' executable not found or not executable."
    echo "Please compile your program using: g++ -std=c++20 -O2 main.cpp -o main"
    echo "And ensure it has execution permissions: chmod +x ./main"
    exit 1
fi

# Function to extract execution time from program output
extract_execution_time() {
    local output="$1"
    echo "$output" | grep -i "Execution time" | awk '{print $(NF-1)}'
}

# Function to extract percent correct from program output
extract_percent_correct() {
    local output="$1"
    local percent=$(echo "$output" | grep -i "Correctness:" | awk '{print $2}' | tr -d '%')

    if [ -z "$percent" ]; then
        percent=$(echo "$output" | grep -i "elements sorted correctly" | awk -F'[()]' '{print $2}' | tr -d '%')
    fi

    echo "$percent"
}

# Set up log file
LOG_FILE="testing_log.txt"
echo "Starting sort testing at $(date)" > $LOG_FILE
echo "Using executable: $(readlink -f ./main)" >> $LOG_FILE

# Progress counter
total_tests=$((${#ALGORITHMS[@]} * ${#TYPES[@]} * ${#SIZES[@]} * ${#SORT_TYPES[@]} * ITERATIONS))
completed=0
start_time=$(date +%s)

# Function to show progress
show_progress() {
    completed=$((completed + 1))
    percentage=$((completed * 100 / total_tests))

    echo -ne "Progress: ${percentage}% ($completed/$total_tests) \r"
}

# Main testing loop
for algorithm in "${ALGORITHMS[@]}"; do
    echo "Testing algorithm: $algorithm" | tee -a $LOG_FILE

    for type in "${TYPES[@]}"; do
        echo "  Data type: $type" | tee -a $LOG_FILE

        for size in "${SIZES[@]}"; do
            echo "    Size: $size" | tee -a $LOG_FILE

            for sort_type in "${SORT_TYPES[@]}"; do
                echo "      Sort type: $sort_type" | tee -a $LOG_FILE

                output_file="results/${algorithm}-${type}-${sort_type}-${size}.csv"
                > "$output_file"

                for ((i=1; i<=ITERATIONS; i++)); do
                    # Validate inputs before calling main
                    if ! [[ "$size" =~ ^[0-9]+$ ]]; then
                        echo "Invalid size value: '$size' is not a number" | tee -a $LOG_FILE
                        continue
                    fi

                    if [[ -z "$algorithm" || -z "$type" || -z "$sort_type" ]]; then
                        echo "Invalid arguments: algorithm=$algorithm, type=$type, sort_type=$sort_type" | tee -a $LOG_FILE
                        continue
                    fi

                    # Log command for debugging
                    echo "Running: ./main --test $algorithm $type $size $sort_type temp_output.txt" >> $LOG_FILE

                    # Run the program and capture output
                    program_output=$(./main --test "$algorithm" "$type" "$size" "$sort_type" "temp_output.txt" 2>&1)
                    status=$?

                    echo "Raw output for $algorithm-$type-$sort_type-$size iteration $i:" >> $LOG_FILE
                    echo "$program_output" >> $LOG_FILE

                    if [ $status -ne 0 ]; then
                        echo "Command failed: ./main --test $algorithm $type $size $sort_type temp_output.txt" >> $LOG_FILE
                        echo "Error: Program failed with exit code $status for $algorithm $type $size $sort_type iteration $i" | tee -a $LOG_FILE
                        continue
                    fi

                    if [ -z "$program_output" ]; then
                        echo "Warning: No output received from program on iteration $i" | tee -a $LOG_FILE
                        continue
                    fi

                    execution_time=$(extract_execution_time "$program_output")
                    percent_correct=$(extract_percent_correct "$program_output")

                    if [ -z "$execution_time" ] || [ -z "$percent_correct" ]; then
                        echo "Warning: Failed to extract metrics for $algorithm-$type-$sort_type-$size iteration $i" | tee -a $LOG_FILE
                        echo "Output was: $program_output" >> $LOG_FILE
                        continue
                    fi

                    echo "$size;$execution_time;$percent_correct" >> "$output_file"
                    show_progress
                done

                echo "      Completed $ITERATIONS iterations for $algorithm-$type-$sort_type-$size" | tee -a $LOG_FILE
            done
        done
    done
done

# Clean up
rm -f temp_output.txt
echo ""
echo "All tests completed at $(date). Results are saved in the 'results' directory." | tee -a $LOG_FILE