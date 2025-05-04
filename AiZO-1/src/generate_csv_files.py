#!/usr/bin/env python3
import os
import csv
import re
from collections import defaultdict

def ensure_directory(directory):
    """Create directory if it doesn't exist."""
    if not os.path.exists(directory):
        os.makedirs(directory)

def read_csv_file(filepath):
    """Read a CSV file and return the correctness percentages."""
    correctness_values = []
    try:
        with open(filepath, 'r') as file:
            for line in file:
                try:
                    parts = line.strip().split(';')
                    if len(parts) >= 3:
                        # Extract the correctness (third field)
                        correctness_values.append(float(parts[2].strip()))
                except ValueError:
                    print(f"Warning: Could not parse line in {filepath}: {line.strip()}")
    except Exception as e:
        print(f"Error reading file {filepath}: {e}")
    
    return correctness_values

def calculate_average(values):
    """Calculate the average of a list of values."""
    if not values:
        return 0.0
    return sum(values) / len(values)

def extract_info_from_filename(filepath):
    """Extract algorithm, type, sort_type, and size from filepath."""
    filename = os.path.basename(filepath)
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
    ensure_directory("./test-1")
    ensure_directory("./test-2")
    ensure_directory("./test-3")
    
    results_dir = "./results"
    if not os.path.exists(results_dir):
        print(f"Error: {results_dir} directory not found!")
        return
    
    csv_files = [os.path.join(results_dir, f) for f in os.listdir(results_dir) if f.endswith(".csv")]
    if not csv_files:
        print(f"Error: No CSV files found in {results_dir}!")
        return
    
    print(f"Found {len(csv_files)} CSV files in {results_dir}")
    
    task1_data = defaultdict(dict)  # {algorithm: {size: avg_correctness}}
    task2_data = defaultdict(dict)  # {algorithm: {sort_type: avg_correctness}}
    task3_data = {}                # {type: avg_correctness}
    
    for filepath in csv_files:
        algorithm, data_type, sort_type, size = extract_info_from_filename(filepath)
        if not all([algorithm, data_type, sort_type, size]):
            continue
        
        correctness_values = read_csv_file(filepath)
        if not correctness_values:
            print(f"Warning: No valid data found in {filepath}")
            continue
        
        avg_correctness = calculate_average(correctness_values)
        
        if data_type == "int" and sort_type == "random":
            task1_data[algorithm][size] = avg_correctness
        
        if data_type == "int" and size == 160000:
            task2_data[algorithm][sort_type] = avg_correctness
        
        if algorithm == "shell" and sort_type == "random" and size == 160000:
            task3_data[data_type] = avg_correctness

    print("\nGenerating Task 1 output files...")
    for algorithm, size_data in task1_data.items():
        output_file = f"./test-1/{algorithm}.csv"
        with open(output_file, 'w', newline='') as file:
            for size, avg_correctness in sorted(size_data.items()):
                file.write(f"{avg_correctness:.2f};{size}\n")
        print(f"  Created {output_file} with {len(size_data)} entries")

    print("\nGenerating Task 2 output files...")
    for algorithm, sort_data in task2_data.items():
        output_file = f"./test-2/{algorithm}.csv"
        with open(output_file, 'w', newline='') as file:
            for sort_type, avg_correctness in sorted(sort_data.items()):
                file.write(f"{avg_correctness:.2f};{sort_type}\n")
        print(f"  Created {output_file} with {len(sort_data)} entries")

    print("\nGenerating Task 3 output files...")
    output_file = "./test-3/types.csv"
    with open(output_file, 'w', newline='') as file:
        for data_type, avg_correctness in sorted(task3_data.items()):
            file.write(f"{avg_correctness:.2f};{data_type}\n")
    print(f"  Created {output_file} with {len(task3_data)} entries")
    
    print("\nCorrectness analysis complete.")

if __name__ == "__main__":
    main()
