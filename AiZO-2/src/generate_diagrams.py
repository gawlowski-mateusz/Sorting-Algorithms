import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set(style="whitegrid")

base_dirs = ["Results-List", "Results-Matrix"]

for base_dir in base_dirs:
    folder_title = base_dir.replace("-", " ")
    for filename in os.listdir(base_dir):
        if filename.endswith(".csv"):
            algorithm_name = filename.replace(".csv", "")
            file_path = os.path.join(base_dir, filename)
            
            df = pd.read_csv(file_path, sep=';', header=None, names=["graph_size", "density", "execution_time"])

            fig, ax = plt.subplots(figsize=(10, 8))
            sns.lineplot(data=df, x="graph_size", y="execution_time", hue="density", marker="o", palette="viridis", ax=ax)

            for _, row in df.iterrows():
                ax.text(row["graph_size"], row["execution_time"], f'{row["execution_time"]:.2f}',
                        fontsize=8, ha='left', va='bottom')

            table_data = df.copy()
            table_data["density"] = table_data["density"].astype(str)
            cell_text = table_data.round(2).values.tolist()
            col_labels = table_data.columns.tolist()

            table = plt.table(cellText=cell_text,
                              colLabels=col_labels,
                              cellLoc='center',
                              colLoc='center',
                              loc='bottom',
                              bbox=[0.0, -0.65, 1.0, 0.5])
            
            table.auto_set_font_size(False)
            table.set_fontsize(8)

            plt.subplots_adjust(left=0.1, bottom=0.35)

            ax.set_title(f"{algorithm_name.capitalize()} Execution Time - {folder_title}")
            ax.set_xlabel("Graph Size (number of vertices)")
            ax.set_ylabel("Execution Time (ms)")
            ax.legend(title="Density")

            plot_filename = f"{base_dir}_{algorithm_name}.png"
            plt.savefig(plot_filename, bbox_inches='tight')
            plt.close()
            print(f"Saved plot with table: {plot_filename}")