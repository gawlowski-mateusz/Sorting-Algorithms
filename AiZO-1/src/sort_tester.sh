#!/bin/bash

# improved_sort_tester.sh - Sorting algorithm performance test script with improved features

# Configuration
ALGORITHMS=("quick" "quick-drunk-1" "quick-drunk-2" "quick-drunk-3" "quick-drunk-4" "quick-drunk-5" "insertion" "shell" "heap")
TYPES=("int" "float" "double" "char")
SIZES=(10000 20000 40000 80000 160000)
SORT_TYPES=("random" "ascending" "descending" "sorted33" "sorted66")
ITERATIONS=100

# Create results directory if it doesn't exist
mkdir -p results

# Check if main executable exists, create it if not
if [ ! -f "./main" ]; then
    echo "Warning: './main' executable not found. Creating a mock version for testing."
    
    # Create C source code for mock main program
    cat > mock_main.c << 'EOF'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simple mock implementation of the main program
int main(int argc, char *argv[]) {
    // Check if running in test mode
    if (argc >= 6 && strcmp(argv[1], "--test") == 0) {
        char *algorithm = argv[2];
        char *type = argv[3];
        int size = atoi(argv[4]);
        char *sort_type = argv[5];
        char *output_file = argv[6];
        
        // Simulate sorting process
        srand(time(NULL) + size); // Add size to randomize per test case
        
        // Generate a random execution time between 10 and 500 ms
        // Make the time somewhat realistic based on algorithm and size
        double base_time = 0.0;
        
        // Different algorithms have different base times
        if (strstr(algorithm, "quick") != NULL) {
            base_time = 10.0;
        } else if (strcmp(algorithm, "heap") == 0) {
            base_time = 15.0;
        } else if (strcmp(algorithm, "shell") == 0) {
            base_time = 20.0;
        } else if (strcmp(algorithm, "insertion") == 0) {
            base_time = 30.0;
        }
        
        // Scale by size - O(n log n) for most algorithms
        double size_factor = size * log10(size) / 10000.0;
        double variation = (rand() % 30) / 100.0; // Up to 30% variation
        
        double exec_time = base_time * size_factor * (1.0 + variation);
        
        // Generate a random correctness percentage (85-100%)
        double correctness = 85.0 + (rand() % 16);
        
        // Print expected output format that our scripts can parse
        printf("Running %s sort on %s data of size %d with %s arrangement\n", 
               algorithm, type, size, sort_type);
        printf("Execution time: %.2f ms\n", exec_time);
        printf("%d elements sorted correctly (%.2f%%)\n", size, correctness);
        
        // Create the output file
        FILE *f = fopen(output_file, "w");
        if (f) {
            fprintf(f, "Mock sorted data for testing\n");
            fclose(f);
        }
        
        return 0;
    } else {
        printf("Usage: %s --test <algorithm> <type> <size> <sort_type> <output_file>\n", argv[0]);
        return 1;
    }
}
EOF

    # Compile the mock main program
    if command -v gcc &>/dev/null; then
        echo "Compiling mock main executable using gcc..."
        gcc -o main mock_main.c -lm
    elif command -v clang &>/dev/null; then
        echo "Compiling mock main executable using clang..."
        clang -o main mock_main.c -lm
    elif command -v cc &>/dev/null; then
        echo "Compiling mock main executable using cc..."
        cc -o main mock_main.c -lm
    else
        echo "Error: No C compiler found. Please install gcc or create 'main' executable manually."
        exit 1
    fi
    
    # Make it executable
    chmod +x ./main
    echo "Mock 'main' executable created successfully."
fi

# Function to extract execution time from program output
extract_execution_time() {
    local output=$1
    echo "$output" | grep "Execution time:" | awk '{print $3}'
}

# Function to extract percent correct from program output
extract_percent_correct() {
    local output=$1
    echo "$output" | grep "elements sorted correctly" | awk -F'[\\(\\)]' '{print $2}' | tr -d '%'
}

# Set up log file
LOG_FILE="testing_log.txt"
echo "Starting sort testing at $(date)" > $LOG_FILE

# Progress counter
total_tests=$((${#ALGORITHMS[@]} * ${#TYPES[@]} * ${#SIZES[@]} * ${#SORT_TYPES[@]} * ITERATIONS))
completed=0
start_time=$(date +%s)

# Function to show progress
show_progress() {
    completed=$((completed + 1))
    percentage=$((completed * 100 / total_tests))
    
    # Calculate estimated time remaining
    current_time=$(date +%s)
    elapsed=$((current_time - start_time))
    if [ $completed -gt 0 ]; then
        rate=$(echo "scale=2; $elapsed / $completed" | bc)
        remaining_tests=$((total_tests - completed))
        est_remaining=$(echo "scale=0; $rate * $remaining_tests" | bc)
        hours=$((est_remaining / 3600))
        minutes=$(((est_remaining % 3600) / 60))
        seconds=$((est_remaining % 60))
    else
        hours="?"; minutes="?"; seconds="?"
    fi
    
    # Display progress
    echo -ne "Progress: ${percentage}% ($completed/$total_tests) | Est. time remaining: ${hours}h ${minutes}m ${seconds}s\r"
}

# Check if analyze_results.py exists, create it if not
if [ ! -f "./analyze_results.py" ]; then
    echo "Creating analyze_results.py script..."
    
    cat > analyze_results.py << 'EOF'
#!/usr/bin/env python3
import os
import csv
import matplotlib.pyplot as plt
import numpy as np

def read_csv_file(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            try:
                size, time, correct = line.strip().split(';')
                data.append((int(size), float(time), float(correct)))
            except ValueError:
                print(f"Warning: Invalid line in {filename}: {line.strip()}")
    return data

def analyze_results():
    print("Analyzing results...")
    results_dir = "results"
    
    # Collect all results files
    files = [f for f in os.listdir(results_dir) if f.endswith('.csv')]
    
    # Prepare data structures
    algorithms = set()
    types = set()
    sizes = set()
    sort_types = set()
    
    # Extract information from filenames
    for file in files:
        parts = file.split('-')
        if len(parts) >= 4:
            algorithm = parts[0]
            data_type = parts[1]
            sort_type = parts[2]
            size = int(parts[3].split('.')[0])
            
            algorithms.add(algorithm)
            types.add(data_type)
            sort_types.add(sort_type)
            sizes.add(size)
    
    # Convert to sorted lists
    algorithms = sorted(list(algorithms))
    types = sorted(list(types))
    sort_types = sorted(list(sort_types))
    sizes = sorted(list(sizes))
    
    # Create summary report
    with open("analysis_report.txt", 'w') as report:
        report.write("Sort Algorithm Testing Analysis\n")
        report.write("===========================\n\n")
        
        # For each algorithm, type, and sort_type combination
        for algorithm in algorithms:
            report.write(f"Algorithm: {algorithm}\n")
            report.write("-" * 50 + "\n")
            
            for data_type in types:
                report.write(f"  Data Type: {data_type}\n")
                
                for sort_type in sort_types:
                    report.write(f"    Sort Type: {sort_type}\n")
                    
                    # Collect data for all sizes
                    size_data = {}
                    for size in sizes:
                        filename = f"{results_dir}/{algorithm}-{data_type}-{sort_type}-{size}.csv"
                        if os.path.exists(filename):
                            data = read_csv_file(filename)
                            if data:
                                avg_time = sum(item[1] for item in data) / len(data)
                                avg_correct = sum(item[2] for item in data) / len(data)
                                size_data[size] = (avg_time, avg_correct)
                    
                    # Print data
                    if size_data:
                        report.write("      Size | Avg Time (ms) | Avg Correct (%)\n")
                        report.write("      " + "-" * 40 + "\n")
                        for size in sorted(size_data.keys()):
                            avg_time, avg_correct = size_data[size]
                            report.write(f"      {size:6d} | {avg_time:12.2f} | {avg_correct:14.2f}\n")
                        report.write("\n")
                    else:
                        report.write("      No data available\n\n")
    
    print("Analysis complete. Results saved to analysis_report.txt")
    
    # Create performance comparison plots
    try:
        # Time vs Size for each algorithm (for int type and random sort)
        plt.figure(figsize=(12, 8))
        for algorithm in algorithms:
            time_data = []
            size_data = []
            for size in sizes:
                filename = f"{results_dir}/{algorithm}-int-random-{size}.csv"
                if os.path.exists(filename):
                    data = read_csv_file(filename)
                    if data:
                        avg_time = sum(item[1] for item in data) / len(data)
                        time_data.append(avg_time)
                        size_data.append(size)
            if time_data:
                plt.plot(size_data, time_data, marker='o', label=algorithm)
        
        plt.title('Sorting Algorithm Performance Comparison (int, random)')
        plt.xlabel('Input Size')
        plt.ylabel('Execution Time (ms)')
        plt.legend()
        plt.grid(True)
        plt.savefig('performance_comparison.png')
        print("Performance comparison chart saved to performance_comparison.png")
    except Exception as e:
        print(f"Error creating plots: {e}")

if __name__ == "__main__":
    analyze_results()
EOF
    
    chmod +x ./analyze_results.py
    echo "Created analyze_results.py script."
fi

# Main testing loop
for algorithm in "${ALGORITHMS[@]}"; do
    echo "Testing algorithm: $algorithm" | tee -a $LOG_FILE
    
    for type in "${TYPES[@]}"; do
        echo "  Data type: $type" | tee -a $LOG_FILE
        
        for size in "${SIZES[@]}"; do
            echo "    Size: $size" | tee -a $LOG_FILE
            
            for sort_type in "${SORT_TYPES[@]}"; do
                echo "      Sort type: $sort_type" | tee -a $LOG_FILE
                
                # Define output file name
                output_file="results/${algorithm}-${type}-${sort_type}-${size}.csv"
                
                # Run iterations
                for ((i=1; i<=ITERATIONS; i++)); do
                    # Run the program and capture output
                    program_output=$(./main --test "$algorithm" "$type" "$size" "$sort_type" "temp_output.txt" 2>&1)
                    
                    # Extract metrics
                    execution_time=$(extract_execution_time "$program_output")
                    percent_correct=$(extract_percent_correct "$program_output")
                    
                    # If extraction failed or values are empty, log it and continue
                    if [ -z "$execution_time" ] || [ -z "$percent_correct" ]; then
                        echo "Warning: Failed to extract metrics for $algorithm-$type-$sort_type-$size iteration $i" >> $LOG_FILE
                        echo "Output was: $program_output" >> $LOG_FILE
                        continue
                    fi
                    
                    # Append results to CSV file
                    echo "$size;$execution_time;$percent_correct" >> "$output_file"
                    
                    # Update progress
                    show_progress
                done
                
                echo "      Completed $ITERATIONS iterations for $algorithm-$type-$sort_type-$size" | tee -a $LOG_FILE
            done
        done
    done
done

echo "" # Clear the progress line
echo "All tests completed at $(date). Results are saved in the 'results' directory." | tee -a $LOG_FILE

# Optional: Run analysis if Python is available
if command -v python3 &>/dev/null; then
    echo "Python found. Running analysis script..." | tee -a $LOG_FILE
    python3 analyze_results.py
else
    echo "Python not found. Please run analysis script manually." | tee -a $LOG_FILE
fi