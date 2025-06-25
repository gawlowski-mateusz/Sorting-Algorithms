import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_style("whitegrid")

base_dirs = ["Results-List", "Results-Matrix"]

# Create output directory if it doesn't exist
output_dir = "Results-Diagrams"
os.makedirs(output_dir, exist_ok=True)

def format_algorithm_name(filename):
    algorithm_name = filename.replace(".csv", "")
    return algorithm_name.replace("-", " ").title()

def create_plot_with_table(df, algorithm_name, folder_title, output_filename):
    fig, ax = plt.subplots(figsize=(12, 10))
    
    sns.lineplot(data=df, x="graph_size", y="execution_time", 
                 hue="density", marker="o", palette="viridis", ax=ax, linewidth=2, markersize=8)

    for _, row in df.iterrows():
        ax.text(row["graph_size"], row["execution_time"], f'{row["execution_time"]:.3f}',
                fontsize=7, ha='center', va='bottom', alpha=0.8)

    pivot_df = df.pivot(index='graph_size', columns='density', values='execution_time')
    
    table_data = []
    for size in pivot_df.index:
        row = [int(size)]
        for density in pivot_df.columns:
            value = pivot_df.loc[size, density]
            row.append(f"{value:.3f}" if pd.notna(value) else "N/A")
        table_data.append(row)
    
    col_labels = ["Graph Size"] + [f"Density {d}" for d in pivot_df.columns]
    
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
    
    plt.savefig(output_filename, bbox_inches='tight', dpi=300, facecolor='white')
    plt.close()
    print(f"Saved plot with table: {output_filename}")

# Main loop for Results-List and Results-Matrix
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
            
            df = pd.read_csv(file_path, sep=';', header=None, 
                             names=["graph_size", "density", "execution_time"])
            
            if df.empty:
                print(f"    Warning: {filename} is empty, skipping...")
                continue
            
            plot_filename = os.path.join(output_dir, f"{base_dir}_{filename.replace('.csv', '')}.png")
            create_plot_with_table(df, algorithm_name, folder_title, plot_filename)
            
        except Exception as e:
            print(f"    Error processing {filename}: {str(e)}")
            continue

# Compare Results-Matrix with Results-SciPy
compare_algorithms = ["dijkstra", "prim", "bellman-ford"]

print("\nGenerating comparison plots between Results-Matrix and SciPyResults...")

for algo in compare_algorithms:
    matrix_file = os.path.join("Results-Matrix", f"{algo}.csv")
    scipy_file = os.path.join("Results-SciPy", f"scipy_{algo.replace('-', '_')}.csv")
    
    if not os.path.exists(matrix_file) or not os.path.exists(scipy_file):
        print(f"  Skipping {algo} – missing file(s)")
        continue
    
    try:
        df_matrix = pd.read_csv(matrix_file, sep=';', header=None, names=["graph_size", "density", "execution_time"])
        df_matrix["source"] = "Custom"
        
        df_scipy = pd.read_csv(scipy_file, sep=';', header=None, names=["graph_size", "density", "execution_time"])
        df_scipy["source"] = "SciPy"

        df_all = pd.concat([df_matrix, df_scipy], ignore_index=True)

        fig, ax = plt.subplots(figsize=(15, 20))
        sns.lineplot(data=df_all, x="graph_size", y="execution_time", 
                     hue="source", style="density", markers=True, dashes=True, palette="Set1", ax=ax)

        ax.set_title(f"{algo.replace('-', ' ').title()} – Custom vs SciPy", fontsize=14, fontweight='bold')
        ax.set_xlabel("Graph Size", fontsize=12)
        ax.set_ylabel("Execution Time (ms)", fontsize=12)
        ax.grid(True, alpha=0.3)
        ax.legend(title="Source / Density", fontsize=10)

        # Create pivoted table
        pivot_df = df_all.pivot_table(index=["graph_size", "density"], columns="source", values="execution_time")
        pivot_df = pivot_df.sort_index().reset_index()

        table_data = []
        for _, row in pivot_df.iterrows():
            gsize = int(row["graph_size"])
            dens = row["density"]
            custom = f"{row['Custom']:.3f}" if pd.notna(row['Custom']) else "N/A"
            scipy = f"{row['SciPy']:.3f}" if pd.notna(row['SciPy']) else "N/A"
            table_data.append([gsize, dens, custom, scipy])

        col_labels = ["Graph Size", "Density", "Custom", "SciPy"]

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

        compare_filename = os.path.join(output_dir, f"Compare_{algo}.png")
        plt.savefig(compare_filename, bbox_inches='tight', dpi=300)
        plt.close()
        print(f"  Saved comparison plot with table: {compare_filename}")
    
    except Exception as e:
        print(f"  Error while comparing {algo}: {str(e)}")

print("\nAll plots generated successfully!")