#include <iostream>
#include <fstream>
#include <string>
#include "./Graph/Graph.h"
#include "./FordFulkerson/FordFulkerson.h"
#include "./Dijkstra/Dijkstra.h"
#include "./BellmanFord/BellmanFord.h"
#include "./Kruskal/Kruskal.h"
#include "./Prim/Prim.h"
#include "./Timer/Timer.h"

using namespace std;

Graph graph;

void printHelp() {
    cout << "\nUsage:\n"
         << "./main --file <algorithm> <inputFile> [outputFile]\n"
         << "./main --test <algorithm> <size> <density> [count] [outputFile]\n"
         << "./main --help\n\n"
         << "Arguments:\n"
         << "  <algorithm>   ford-fulkerson-bfs | ford-fulkerson-dfs | bellman-ford | dijkstra | kruskal | prim\n"
         << "  <inputFile>   Path to graph file\n"
         << "  <size>        Number of vertices (for test mode)\n"
         << "  <density>     Edge density (0.0 to 1.0)\n"
         << "  <count>       Number of test repetitions (default: 1)\n"
         << "  <outputFile>  Optional CSV log file to store: size;density;avgTime\n\n"
         << "Examples:\n"
         << "  ./main --file dijkstra ./input.txt results.csv\n"
         << "  ./main --test prim 15 1.0 50 results.csv\n";
}

void handleFileMode(const string& algorithm, const string& inputFile, const string& outputFile = "") {
    int startingVertex = 0;
    int endVertex;
    
    if (graph.loadFromFileMst(inputFile) != 0) {
        cerr << "Failed to load graph from file: " << inputFile << '\n';
        return;
    }
    
    endVertex = graph.getVerticesNumber() - 1;

    Timer timer;
    timer.start();

    if (algorithm == "ford-fulkerson-bfs") {
        FordFulkerson fordFulkerson(graph);
        cout << "FordFulkerson BFS" << endl;
        fordFulkerson.fordFulkersonBFSAdjacencyMatrix(startingVertex, endVertex);
    } else if (algorithm == "ford-fulkerson-dfs") {
        FordFulkerson fordFulkerson(graph);
        cout << "FordFulkerson DFS" << endl;
        fordFulkerson.fordFulkersonDFSAdjacencyMatrix(startingVertex, endVertex);
    } else if (algorithm == "bellman-ford") {
        BellmanFord bellmanFord(graph);
        bellmanFord.bellmanFordAdjacencyList(startingVertex);
        bellmanFord.bellmanFordAdjacencyMatrix(startingVertex);
    } else if (algorithm == "dijkstra") {
        Dijkstra dijkstra(graph);
        dijkstra.dijkstraAdjacencyList(startingVertex);
        dijkstra.dijkstraAdjacencyMatrix(startingVertex);
    } else if (algorithm == "prim") {
        Prim prim(graph);
        prim.primAdjacencyList();
        prim.primAdjacencyMatrix();
    } else if (algorithm == "kruskal") {
        Kruskal kruskal(graph);
        kruskal.kruskalAdjacencyList();
        kruskal.kruskalAdjacencyMatrix();
    } else {
        cerr << "Unknown algorithm: " << algorithm << '\n';
        return;
    }

    timer.stop();
    double execTime = timer.result();
    cout << "Execution time: " << execTime << " ms\n";

    if (!outputFile.empty()) {
        ofstream out(outputFile, ios::app);
        if (!out) {
            cerr << "Failed to open output file: " << outputFile << "\n";
        } else {
            out << graph.getVerticesNumber() << ";N/A;" << execTime << "\n";
            out.close();
            cout << "Saved result to: " << outputFile << "\n";
        }
    }
}

void handleTestMode(const string& algorithm, int size, double density, int count = 1, const string& outputFile = "") {
    if (density < 0.0 || density > 1.0) {
        cerr << "Density must be between 0 and 1.\n";
        return;
    }

    double totalTime = 0.0;

    for (int i = 0; i < count; ++i) {
        cout << "Run #" << i + 1 << " of " << count << "\n";

        Graph tempGraph;
        tempGraph.generateUndirectedGraph(size, density);

        int startingVertex = 0;
        int endVertex = size - 1;

        Timer timer;
        timer.start();

        if (algorithm == "ford-fulkerson-bfs") {
            FordFulkerson fordFulkerson(tempGraph);
            fordFulkerson.fordFulkersonBFSAdjacencyMatrix(startingVertex, endVertex);
        } else if (algorithm == "ford-fulkerson-dfs") {
            FordFulkerson fordFulkerson(tempGraph);
            fordFulkerson.fordFulkersonDFSAdjacencyMatrix(startingVertex, endVertex);
        } else if (algorithm == "dijkstra") {
            Dijkstra dijkstra(tempGraph);
            // dijkstra.dijkstraAdjacencyList(startingVertex);
            dijkstra.dijkstraAdjacencyMatrix(startingVertex);
        } else if (algorithm == "bellman-ford") {
            BellmanFord bellmanFord(tempGraph);
            // bellmanFord.bellmanFordAdjacencyList(startingVertex);
            bellmanFord.bellmanFordAdjacencyMatrix(startingVertex);
        } else if (algorithm == "kruskal") {
            Kruskal kruskal(tempGraph);
            // kruskal.kruskalAdjacencyList();
            kruskal.kruskalAdjacencyMatrix();
        } else if (algorithm == "prim") {
            Prim prim(tempGraph);
            // prim.primAdjacencyList();
            prim.primAdjacencyMatrix();
        } else {
            cerr << "Unknown algorithm: " << algorithm << '\n';
            return;
        }

        timer.stop();
        double time = timer.result();
        totalTime += time;

        cout << "Execution time: " << time << " ms\n";
        cout << "-----------------------------\n";
    }

    double avgTime = totalTime / count;
    cout << "\nAverage execution time over " << count << " runs: "
         << avgTime << " ms\n";

    if (!outputFile.empty()) {
        ofstream out(outputFile, ios::app);
        if (!out) {
            cerr << "Failed to open output file: " << outputFile << "\n";
        } else {
            out << size << ";" << density << ";" << avgTime << "\n";
            out.close();
            cout << "Saved result to: " << outputFile << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    cout << "DEBUG: Program started\n";
    
    if (argc < 2) {
        cerr << "Missing arguments. Use --help for usage.\n";
        return 1;
    }

    string mode = argv[1];
    cout << "DEBUG: Mode: " << mode << "\n";

    if (mode == "--help") {
        printHelp();
        return 0;
    } else if (mode == "--file") {
        if (argc < 4) {
            cerr << "Usage: ./main --file <algorithm> <inputFile> [outputFile]\n";
            return 1;
        }

        string algorithm = argv[2];
        string inputFile = argv[3];
        string outputFile = (argc >= 5) ? argv[4] : "";
        handleFileMode(algorithm, inputFile, outputFile);
    } else if (mode == "--test") {
        if (argc < 5) {
            cerr << "Usage: ./main --test <algorithm> <size> <density> [count] [outputFile]\n";
            return 1;
        }

        string algorithm = argv[2];
        int size = stoi(argv[3]);
        double density = stod(argv[4]);

        int count = 1;
        if (argc >= 6) {
            count = stoi(argv[5]);
            if (count < 1) {
                cerr << "Count must be a positive integer.\n";
                return 1;
            }
        }

        string outputFile = "";
        if (argc >= 7) {
            outputFile = argv[6];
        }

        handleTestMode(algorithm, size, density, count, outputFile);
    } else {
        cerr << "Unknown mode. Use --help for usage.\n";
        return 1;
    }

    cout << "DEBUG: Program ending normally\n";
    return 0;
}