import numpy as np
from scipy.sparse import random as sparse_random
from scipy.sparse.csgraph import dijkstra, bellman_ford, minimum_spanning_tree
import time
import os

INT_MAX = np.iinfo(np.int32).max

def generate_random_sparse_graph(size, density):
    def int_weight_gen(nz):
        return np.random.randint(1, INT_MAX, size=nz)

    graph = sparse_random(
        size,
        size,
        density=density,
        format="csr",
        data_rvs=int_weight_gen,
        dtype=np.float64
    )

    graph.setdiag(0)
    graph.eliminate_zeros()

    return graph

def benchmark_scipy_dijkstra():
    sizes = [10, 20, 50, 100, 200, 500, 1000]
    densities = [0.25, 0.5, 0.99]
    repetitions = 100
    output_file = "./Results-SciPy/scipy_dijkstra.csv"

    with open(output_file, 'w') as f:
        for size in sizes:
            for density in densities:
                total_time_ms = 0.0
                for _ in range(repetitions):
                    start = time.perf_counter()
                    graph = generate_random_sparse_graph(size, density)
                    _ = dijkstra(csgraph=graph, directed=True, indices=0)
                    end = time.perf_counter()
                    exec_time_ms = (end - start) * 1000
                    total_time_ms += exec_time_ms

                average_time = total_time_ms / repetitions
                f.write(f"{size};{density:.3f};{average_time:.3f}\n")
                print(f"Dijkstra {size};{density:.3f};{average_time:.3f}")
                
def benchmark_scipy_bellman_ford():
    sizes = [10, 20, 50, 100, 200, 500, 1000]
    densities = [0.25, 0.5, 0.99]
    repetitions = 100
    output_file = "./Results-SciPy/scipy_bellman_ford.csv"

    with open(output_file, 'w') as f:
        for size in sizes:
            for density in densities:
                total_time_ms = 0.0
                for _ in range(repetitions):
                    graph = generate_random_sparse_graph(size, density)
                    start = time.perf_counter()
                    _ = bellman_ford(csgraph=graph, directed=True, indices=0)
                    end = time.perf_counter()
                    total_time_ms += (end - start) * 1000
                average_time = total_time_ms / repetitions
                f.write(f"{size};{density:.3f};{average_time:.3f}\n")
                print(f"Bellman-Ford {size};{density:.3f};{average_time:.3f}")

def benchmark_scipy_prim():
    sizes = [10, 20, 50, 100, 200, 500, 1000]
    densities = [0.25, 0.5, 0.99]
    repetitions = 100
    output_file = "./Results-SciPy/scipy_prim.csv"

    with open(output_file, 'w') as f:
        for size in sizes:
            for density in densities:
                total_time_ms = 0.0
                for _ in range(repetitions):
                    graph = generate_random_sparse_graph(size, density)
                    undirected_graph = (graph + graph.T) / 2
                    start = time.perf_counter()
                    _ = minimum_spanning_tree(undirected_graph)
                    end = time.perf_counter()
                    total_time_ms += (end - start) * 1000
                average_time = total_time_ms / repetitions
                f.write(f"{size};{density:.3f};{average_time:.3f}\n")
                print(f"Prim {size};{density:.3f};{average_time:.3f}")

if __name__ == "__main__":
    os.makedirs("./Results-SciPy", exist_ok=True)
    benchmark_scipy_dijkstra()
    benchmark_scipy_bellman_ford()
    benchmark_scipy_prim()
