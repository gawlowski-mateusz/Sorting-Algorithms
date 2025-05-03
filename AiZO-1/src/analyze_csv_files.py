import os
import pandas as pd
import matplotlib.pyplot as plt
import glob

def process_test1_files(directory):
    """
    Process files in test-1 directory.
    Format: execution_time;List_size
    """
    # Create output directory
    output_directory = directory + "-diagrams"
    os.makedirs(output_directory, exist_ok=True)
    
    csv_files = glob.glob(os.path.join(directory, "*.csv"))
    
    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))
        
        # Read data
        try:
            df = pd.read_csv(csv_file, sep=';', header=None, names=['execution_time', 'list_size'])
            
            # Create plot
            plt.figure(figsize=(10, 6))
            plt.plot(df['list_size'], df['execution_time'], 'o-', linewidth=2, markersize=8)
            plt.xlabel('List Size')
            plt.ylabel('Execution Time (ms)')
            plt.title(f'Execution Time vs List Size: {filename}')
            plt.grid(True)
            plt.xscale('log')  # Log scale for list size as it often grows exponentially
            
            # Save plot
            plt.savefig(output_file, dpi=300, bbox_inches='tight')
            plt.close()
            print(f"Generated {output_file}")
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def process_test2_files(directory):
    """
    Process files in test-2 directory.
    Format: time;list_sort_type
    """
    # Create output directory
    output_directory = directory + "-diagrams"
    os.makedirs(output_directory, exist_ok=True)
    
    csv_files = glob.glob(os.path.join(directory, "*.csv"))
    
    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))
        
        try:
            # Read data
            df = pd.read_csv(csv_file, sep=';', header=None, names=['time', 'sort_type'])
            
            # Create bar plot
            plt.figure(figsize=(12, 6))
            bars = plt.bar(df['sort_type'], df['time'])
            
            # Add data labels on top of bars
            for bar in bars:
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width()/2., height + 5,
                         f'{height:.2f}',
                         ha='center', va='bottom', rotation=0)
            
            plt.xlabel('List Sort Type')
            plt.ylabel('Time (ms)')
            plt.title(f'Execution Time by Sort Type: {filename}')
            plt.grid(True, axis='y')
            plt.xticks(rotation=45)
            
            # Save plot
            plt.savefig(output_file, dpi=300, bbox_inches='tight')
            plt.close()
            print(f"Generated {output_file}")
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def process_test3_files(directory):
    """
    Process files in test-3 directory.
    Format: time;data_type
    """
    # Create output directory
    output_directory = directory + "-diagrams"
    os.makedirs(output_directory, exist_ok=True)
    
    csv_files = glob.glob(os.path.join(directory, "*.csv"))
    
    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))
        
        try:
            # Read data
            df = pd.read_csv(csv_file, sep=';', header=None, names=['time', 'data_type'])
            
            # Create bar plot with distinct colors
            plt.figure(figsize=(10, 6))
            bars = plt.bar(df['data_type'], df['time'], color=['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728'])
            
            # Add data labels on top of bars
            for bar in bars:
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width()/2., height + 5,
                         f'{height:.2f}',
                         ha='center', va='bottom')
            
            plt.xlabel('Data Type')
            plt.ylabel('Time (ms)')
            plt.title(f'Execution Time by Data Type: {filename}')
            plt.grid(True, axis='y')
            
            # Save plot
            plt.savefig(output_file, dpi=300, bbox_inches='tight')
            plt.close()
            print(f"Generated {output_file}")
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def main():
    # Process each test directory
    directories = ['./test-1', './test-2', './test-3']
    
    for directory in directories:
        if not os.path.exists(directory):
            print(f"Directory {directory} does not exist")
            continue
            
        print(f"Processing files in {directory}...")
        
        if 'test-1' in directory:
            process_test1_files(directory)
        elif 'test-2' in directory:
            process_test2_files(directory)
        elif 'test-3' in directory:
            process_test3_files(directory)
            
    print("Processing complete!")

if __name__ == "__main__":
    main()
    