#!/usr/bin/env python3
import os
import csv
import re
import statistics
from collections import defaultdict

def ensure_directory(directory):
    """Create directory if it doesn't exist."""
    if not os.path.exists(directory):
        os.makedirs(directory)

def read_csv_file(filepath):
    """Read a CSV file and return the execution times."""
    times = []
    try:
        with open(filepath, 'r') as file:
            for line in file:
                try:
                    parts = line.strip().split(';')
                    if len(parts) >= 2:
                        # Extract the execution time (second field)
                        times.append(float(parts[1].strip()))
                except ValueError as e:
                    print(f"Warning: Could not parse line in {filepath}: {line.strip()}")
    except Exception as e:
        print(f"Error reading file {filepath}: {e}")
    
    return times

def calculate_average(times):
    """Calculate the average of a list of times."""
    if not times:
        return 0.0
    return sum(times) / len(times)

def extract_info_from_filename(filepath):
    """Extract algorithm, type, sort_type, and size from filepath."""
    # Extract just the filename from the path
    filename = os.path.basename(filepath)
    
    # Expected format: algorithm-type-sort_type-size.csv
    pattern = r"^([\w-]+)-([\w]+)-([\w\d]+)-(\d+)\.csv$"
    match = re.match(pattern, filename)
    
    if match:
        algorithm = match.group(1)
        data_type = match.group(2)
        sort_type = match.group(3)
        size = int(match.group(4))
        return algorithm, data_type, sort_type, size
    
    print(f"Warning: Could not parse filename: {filename}")
    return None, None, None, None

def main():
    # Create output directories
    ensure_directory("./test-1")
    ensure_directory("./test-2")
    ensure_directory("./test-3")
    
    # Collect all CSV files in the ./results directory
    results_dir = "./results"
    if not os.path.exists(results_dir):
        print(f"Error: {results_dir} directory not found!")
        return
    
    csv_files = [os.path.join(results_dir, f) for f in os.listdir(results_dir) if f.endswith(".csv")]
    
    if not csv_files:
        print(f"Error: No CSV files found in {results_dir}!")
        return
    
    print(f"Found {len(csv_files)} CSV files in {results_dir}")
    
    # Dictionaries to store results
    task1_data = defaultdict(dict)  # {algorithm: {size: avg_time}}
    task2_data = defaultdict(dict)  # {algorithm: {sort_type: avg_time}}
    task3_data = {}                # {type: avg_time}
    
    # Process all CSV files
    for filepath in csv_files:
        algorithm, data_type, sort_type, size = extract_info_from_filename(filepath)
        
        if not all([algorithm, data_type, sort_type, size]):
            continue
        
        # Read the file and calculate average execution time
        times = read_csv_file(filepath)
        if not times:
            print(f"Warning: No valid data found in {filepath}")
            continue
            
        avg_time = calculate_average(times)
        
        # Task 1: <algorithm>-int-random-<size>
        if data_type == "int" and sort_type == "random":
            task1_data[algorithm][size] = avg_time
        
        # Task 2: <algorithm>-int-<sort>-160000
        if data_type == "int" and size == 160000:
            task2_data[algorithm][sort_type] = avg_time
        
        # Task 3: shell-<type>-random-160000
        if algorithm == "shell" and sort_type == "random" and size == 160000:
            task3_data[data_type] = avg_time
    
    # Generate output for Task 1
    print("\nGenerating Task 1 output files...")
    for algorithm, size_data in task1_data.items():
        output_file = f"./test-1/{algorithm}.csv"
        with open(output_file, 'w', newline='') as file:
            for size, avg_time in sorted(size_data.items()):
                file.write(f"{avg_time:.6f};{size}\n")
        print(f"  Created {output_file} with {len(size_data)} entries")
    
    # Generate output for Task 2
    print("\nGenerating Task 2 output files...")
    for algorithm, sort_data in task2_data.items():
        output_file = f"./test-2/{algorithm}.csv"
        with open(output_file, 'w', newline='') as file:
            for sort_type, avg_time in sorted(sort_data.items()):
                file.write(f"{avg_time:.6f};{sort_type}\n")
        print(f"  Created {output_file} with {len(sort_data)} entries")
    
    # Generate output for Task 3
    print("\nGenerating Task 3 output files...")
    output_file = "./test-3/types.csv"
    with open(output_file, 'w', newline='') as file:
        for data_type, avg_time in sorted(task3_data.items()):
            file.write(f"{avg_time:.6f};{data_type}\n")
    print(f"  Created {output_file} with {len(task3_data)} entries")
    
    print("\nAnalysis complete.")

if __name__ == "__main__":
    main()
    