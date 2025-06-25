#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "./Graph/Graph.h"
#include "./FordFulkerson/FordFulkerson.h"
#include "./Dijkstra/Dijkstra.h"
#include "./BellmanFord/BellmanFord.h"
#include "./Kruskal/Kruskal.h"
#include "./Prim/Prim.h"
#include "./Timer/Timer.h"

using namespace std;

void handleTestMode(const string& algorithm, int size, double density, int count = 1, const string& outputFile = "") {
    if (density < 0.0 || density > 1.0) {
        cerr << "Density must be between 0 and 1.\n";
        return;
    }

    double totalTime = 0.0;

    for (int i = 0; i < count; ++i) {
        cout << "Run #" << i + 1 << " of " << count << "\n";

        Graph tempGraph;

        int startingVertex = 0;
        int endVertex = size - 1;
        auto preciseStart = std::chrono::high_resolution_clock::now();
        
        Timer timer;
        timer.start();

        if (algorithm == "ford-fulkerson-bfs") {
            tempGraph.generateDirectedGraph(size, density);
            FordFulkerson fordFulkerson(tempGraph);
            fordFulkerson.fordFulkersonBFSAdjacencyMatrix(startingVertex, endVertex);
        } else if (algorithm == "ford-fulkerson-dfs") {
            tempGraph.generateDirectedGraph(size, density);
            FordFulkerson fordFulkerson(tempGraph);
            fordFulkerson.fordFulkersonDFSAdjacencyMatrix(startingVertex, endVertex);
        } else if (algorithm == "dijkstra") {
            tempGraph.generateDirectedGraph(size, density);
            Dijkstra dijkstra(tempGraph);
            // dijkstra.dijkstraAdjacencyList(startingVertex);
            dijkstra.dijkstraAdjacencyMatrix(startingVertex);
        } else if (algorithm == "bellman-ford") {
            tempGraph.generateDirectedGraph(size, density);
            BellmanFord bellmanFord(tempGraph);
            // bellmanFord.bellmanFordAdjacencyList(startingVertex);
            bellmanFord.bellmanFordAdjacencyMatrix(startingVertex);
        } else if (algorithm == "kruskal") {
            tempGraph.generateUndirectedGraph(size, density);
            Kruskal kruskal(tempGraph);
            // kruskal.kruskalAdjacencyList();
            kruskal.kruskalAdjacencyMatrix();
        } else if (algorithm == "prim") {
            tempGraph.generateUndirectedGraph(size, density);
            Prim prim(tempGraph);
            // prim.primAdjacencyList();
            prim.primAdjacencyMatrix();
        } else {
            cerr << "Unknown algorithm: " << algorithm << '\n';
            return;
        }

        timer.stop();
        auto preciseEnd = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(preciseEnd - preciseStart);
        double time = duration.count() / 1000000.0;
        
        totalTime += time;

        cout << fixed << setprecision(3);
        cout << "Execution time: " << time << " ms\n";
        cout << "-----------------------------\n";
    }

    double avgTime = totalTime / count;
    cout << fixed << setprecision(3);
    cout << "\nAverage execution time over " << count << " runs: "
         << avgTime << " ms\n";

    if (!outputFile.empty()) {
        ofstream out(outputFile, ios::app);
        if (!out) {
            cerr << "Failed to open output file: " << outputFile << "\n";
        } else {
            out << fixed << setprecision(3);
            out << size << ";" << density << ";" << avgTime << "\n";
            out.close();
            cout << "Saved result to: " << outputFile << "\n";
        }
    }
}

void runAllTests() {
    vector<int> sizes = {10, 20, 50, 100, 200, 500, 1000};
    vector<double> densities = {0.25, 0.5, 0.99};
    int count = 20;

    vector<pair<string, string>> algorithms = {
        {"dijkstra", "./Results/dijkstra.csv"},
        {"bellman-ford", "./Results/bellman-ford.csv"},
        {"kruskal", "./Results/kruskal.csv"},
        {"prim", "./Results/prim.csv"},
        {"ford-fulkerson-dfs", "./Results/ford-fulkerson-dfs.csv"},
        {"ford-fulkerson-bfs", "./Results/ford-fulkerson-bfs.csv"}
    };

    for (const auto& [algorithm, outputFile] : algorithms) {
        cout << "\n=== Running tests for algorithm: " << algorithm << " ===\n";
        for (int size : sizes) {
            for (double density : densities) {
                cout << "Testing with size = " << size << ", density = " << density << "\n";
                handleTestMode(algorithm, size, density, count, outputFile);
            }
        }
    }
}

int main(int /*argc*/, char* /*argv*/[]) {
    const char* resultsDir = "./Results";
    if (mkdir(resultsDir, 0777) && errno != EEXIST) {
        cerr << "Error creating directory: " << resultsDir << '\n';
        return 1;
    }

    runAllTests();
    return 0;
}