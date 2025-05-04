import os
import pandas as pd
import matplotlib.pyplot as plt
import glob

def ensure_output_dir(directory):
    output_directory = directory + "-diagrams"
    os.makedirs(output_directory, exist_ok=True)
    return output_directory

def save_and_close_plot(output_file):
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Generated {output_file}")

def process_test1_files(directory):
    """
    Process files in test-1 directory.
    Format: correctness;list_size
    """
    output_directory = ensure_output_dir(directory)
    csv_files = glob.glob(os.path.join(directory, "*.csv"))

    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))

        try:
            df = pd.read_csv(csv_file, sep=';', header=None, names=['correctness', 'list_size'])
            df.sort_values(by='list_size', inplace=True)

            plt.figure(figsize=(10, 6))
            plt.plot(df['list_size'], df['correctness'], marker='o', linestyle='-', color='#1f77b4')

            for _, row in df.iterrows():
                plt.annotate(f"{int(row['list_size'])}, {row['correctness']:.1f}%",
                             (row['list_size'], row['correctness']),
                             textcoords="offset points", xytext=(0, 8),
                             ha='center', fontsize=9)

            plt.xlabel('List Size', fontsize=12)
            plt.ylabel('Correctly Sorted (%)', fontsize=12)
            plt.title(f'Sorting Accuracy vs List Size\n{filename}', fontsize=14)
            plt.grid(True, linestyle='--', alpha=0.7)
            plt.xticks(df['list_size'], rotation=45)
            plt.tight_layout()

            save_and_close_plot(output_file)
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def process_test2_files(directory):
    """
    Process files in test-2 directory.
    Format: correctness;sort_type
    """
    output_directory = ensure_output_dir(directory)
    csv_files = glob.glob(os.path.join(directory, "*.csv"))

    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))

        try:
            df = pd.read_csv(csv_file, sep=';', header=None, names=['correctness', 'sort_type'])

            plt.figure(figsize=(12, 6))
            bars = plt.bar(df['sort_type'], df['correctness'], color='#2ca02c')

            for bar, correctness in zip(bars, df['correctness']):
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width() / 2., height + 1,
                         f'{correctness:.1f}%',
                         ha='center', va='bottom', fontsize=10)

            plt.xlabel('Sort Type', fontsize=12)
            plt.ylabel('Correctly Sorted (%)', fontsize=12)
            plt.title(f'Sorting Accuracy by Sort Type\n{filename}', fontsize=14)
            plt.grid(True, axis='y', linestyle='--', alpha=0.7)
            plt.xticks(rotation=45)
            plt.tight_layout()

            save_and_close_plot(output_file)
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def process_test3_files(directory):
    """
    Process files in test-3 directory.
    Format: correctness;data_type
    """
    output_directory = ensure_output_dir(directory)
    csv_files = glob.glob(os.path.join(directory, "*.csv"))

    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        output_file = os.path.join(output_directory, filename.replace('.csv', '.jpg'))

        try:
            df = pd.read_csv(csv_file, sep=';', header=None, names=['correctness', 'data_type'])

            plt.figure(figsize=(10, 6))
            colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
            bars = plt.bar(df['data_type'], df['correctness'], color=colors[:len(df)])

            for bar, correctness in zip(bars, df['correctness']):
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width() / 2., height + 1,
                         f'{correctness:.1f}%',
                         ha='center', va='bottom', fontsize=10)

            plt.xlabel('Data Type', fontsize=12)
            plt.ylabel('Correctly Sorted (%)', fontsize=12)
            plt.title(f'Sorting Accuracy by Data Type\n{filename}', fontsize=14)
            plt.grid(True, axis='y', linestyle='--', alpha=0.7)
            plt.tight_layout()

            save_and_close_plot(output_file)
        except Exception as e:
            print(f"Error processing {csv_file}: {e}")

def main():
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
