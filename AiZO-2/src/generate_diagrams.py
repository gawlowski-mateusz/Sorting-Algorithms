import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_style("whitegrid")

base_dirs = ["Results-List", "Results-Matrix"]

def format_algorithm_name(filename):
    """Format algorithm name for display"""
    algorithm_name = filename.replace(".csv", "")
    return algorithm_name.replace("-", " ").title()

def create_plot_with_table(df, algorithm_name, folder_title, output_filename):
    """Create a plot with data table for the given dataframe"""
    fig, ax = plt.subplots(figsize=(12, 10))
    
    # Create the line plot
    sns.lineplot(data=df, x="graph_size", y="execution_time", 
                hue="density", marker="o", palette="viridis", ax=ax, linewidth=2, markersize=8)

    # Add data labels on points
    for _, row in df.iterrows():
        ax.text(row["graph_size"], row["execution_time"], f'{row["execution_time"]:.3f}',
                fontsize=7, ha='center', va='bottom', alpha=0.8)

    pivot_df = df.pivot(index='graph_size', columns='density', values='execution_time')
    
    # Create table data
    table_data = []
    for size in pivot_df.index:
        row = [int(size)]
        for density in pivot_df.columns:
            value = pivot_df.loc[size, density]
            if pd.notna(value):
                row.append(f"{value:.3f}")
            else:
                row.append("N/A")
        table_data.append(row)
    
    col_labels = ["Graph Size"] + [f"Density {d}" for d in pivot_df.columns]
    
    # Create table
    table = plt.table(cellText=table_data,
                      colLabels=col_labels,
                      cellLoc='center',
                      colLoc='center',
                      loc='bottom',
                      bbox=[0.0, -0.6, 1.0, 0.4])
    
    table.auto_set_font_size(False)
    table.set_fontsize(9)
    table.scale(1, 1.5)
    
    for i in range(len(col_labels)):
        table[(0, i)].set_facecolor('#40466e')
        table[(0, i)].set_text_props(weight='bold', color='white')
    
    plt.subplots_adjust(left=0.1, bottom=0.4, top=0.9)

    ax.set_title(f"{algorithm_name} Execution Time - {folder_title}", fontsize=14, fontweight='bold', pad=20)
    ax.set_xlabel("Graph Size (number of vertices)", fontsize=12)
    ax.set_ylabel("Execution Time (ms)", fontsize=12)
    ax.legend(title="Density", title_fontsize=10, fontsize=9)
    
    ax.grid(True, alpha=0.3)
    
    # Save the plot
    plt.savefig(output_filename, bbox_inches='tight', dpi=300, facecolor='white')
    plt.close()
    print(f"Saved plot with table: {output_filename}")

for base_dir in base_dirs:
    if not os.path.exists(base_dir):
        print(f"Directory {base_dir} not found, skipping...")
        continue
        
    folder_title = base_dir.replace("-", " ")
    csv_files = [f for f in os.listdir(base_dir) if f.endswith(".csv")]
    
    if not csv_files:
        print(f"No CSV files found in {base_dir}")
        continue
    
    print(f"\nProcessing {base_dir}:")
    print(f"Found {len(csv_files)} CSV files: {csv_files}")
    
    for filename in csv_files:
        try:
            algorithm_name = format_algorithm_name(filename)
            file_path = os.path.join(base_dir, filename)
            
            print(f"  Processing: {filename}")
            
            # Read CSV file
            df = pd.read_csv(file_path, sep=';', header=None, 
                           names=["graph_size", "density", "execution_time"])
            
            if df.empty:
                print(f"    Warning: {filename} is empty, skipping...")
                continue
            
            # Create output filename
            plot_filename = f"{base_dir}_{filename.replace('.csv', '')}.png"
            
            create_plot_with_table(df, algorithm_name, folder_title, plot_filename)
            
        except Exception as e:
            print(f"    Error processing {filename}: {str(e)}")
            continue

print("\nAll plots generated successfully!")