#include <iostream>
#include <fstream>
#include <string>
#include "./Graph/Graph.h"
#include "./FordFulkerson/FordFulkerson.h"
#include "./Dijkstra/Dijkstra.h"
#include "./BellmanFord/BellmanFord.h"
#include "./Kruskal/Kruskal.h"
#include "./Prim/Prim.h"

using namespace std;

Graph graph;

void printHelp() {
    cout << "\nUsage:\n"
         << "./main --file <algorithm> <inputFile>\n"
         << "./main --test <algorithm> <size> <density>\n"
         << "./main --help\n\n"
         << "Arguments:\n"
        << "  <algorithm>   ford-fulkerson-bfs | ford-fulkerson-dfs | bellman-ford | dijkstra  | kruskal | prim\n"
         << "  <inputFile>   Path to graph file\n"
         << "  <size>        Number of vertices\n"
         << "  <density>     Edge density (0.0 to 1.0)\n\n"
         << "Examples:\n"
         << "  ./main --file dijkstra ./input.txt\n"
         << "  ./main --test ford-fulkerson-bfs 10 0.6\n";
}

void handleFileMode(const string& algorithm, const string& inputFile) {
    int startingVertex = 0;
    int endVertex;
    
    if (graph.loadFromFileMst(inputFile) != 0) {
        cerr << "Failed to load graph from file: " << inputFile << '\n';
        return;
    }
    
    endVertex = graph.getVerticesNumber() - 1;

    if (algorithm == "ford-fulkerson-bfs") {
        FordFulkerson fordFulkerson(graph);
        cout << "FordFulkerson BFS" << endl;
        fordFulkerson.fordFulkersonBFSAdjacencyMatrix(startingVertex, endVertex);
    } else if (algorithm == "ford-fulkerson-dfs") {
        FordFulkerson fordFulkerson(graph);
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
    }
}

void handleTestMode(const string& algorithm, int size, double density) {
    cout << "DEBUG: Starting handleTestMode\n";
    cout << "DEBUG: Algorithm: " << algorithm << ", Size: " << size << ", Density: " << density << "\n";

    if (density < 0.0 || density > 1.0) {
        cerr << "Density must be between 0 and 1.\n";
        return;
    }

    cout << "DEBUG: Creating Graph object\n";
    
    cout << "DEBUG: Graph created, calling generateDirectedGraph\n";
    graph.generateUndirectedGraph(size, density);

    graph.print();
    
    cout << "DEBUG: Graph generated successfully\n";
    cout << "DEBUG: Vertices: " << graph.getVerticesNumber() << "\n";
    cout << "DEBUG: Edges: " << graph.getEdgeNumber() << "\n";

    int startingVertex = 0;
    int endVertex = size - 1;

    if (algorithm == "ford-fulkerson-bfs") {
        cout << "DEBUG: Creating FordFulkerson solver\n";
        FordFulkerson fordFulkerson(graph);
        cout << "FordFulkerson BFS" << endl;
        fordFulkerson.fordFulkersonBFSAdjacencyMatrix(startingVertex, endVertex);
    } else if (algorithm == "ford-fulkerson-dfs") {
        cout << "DEBUG: Creating FordFulkerson solver\n";
        FordFulkerson fordFulkerson(graph);
        cout << "FordFulkerson DFS" << endl;
        fordFulkerson.fordFulkersonDFSAdjacencyMatrix(startingVertex, endVertex);
    } else if (algorithm == "dijkstra") {
        cout << "DEBUG: Creating Dijkstra solver\n";
        try {
            Dijkstra dijkstra(graph);
            cout << "DEBUG: Dijkstra solver created, calling dijkstraAdjacencyList\n";
            dijkstra.dijkstraAdjacencyList(startingVertex);
            dijkstra.dijkstraAdjacencyMatrix(startingVertex);
            cout << "DEBUG: Dijkstra completed successfully\n";
        } catch (const exception& e) {
            cerr << "DEBUG: Exception in Dijkstra: " << e.what() << "\n";
        } catch (...) {
            cerr << "DEBUG: Unknown exception in Dijkstra\n";
        }
    } else if (algorithm == "bellman-ford") {
        cout << "DEBUG: Creating BellmanFord solver\n";
        BellmanFord bellmanFord(graph);
        bellmanFord.bellmanFordAdjacencyList(startingVertex);
        bellmanFord.bellmanFordAdjacencyMatrix(startingVertex);
    } else if (algorithm == "kruskal") {
        cout << "DEBUG: Creating Kruskal solver\n";
        Kruskal kruskal(graph);
        kruskal.kruskalAdjacencyList();
        kruskal.kruskalAdjacencyMatrix();
    } else if (algorithm == "prim") {
        cout << "DEBUG: Creating Prim solver\n";
        Prim prim(graph);
        prim.primAdjacencyList();
        prim.primAdjacencyMatrix();
    } else {
        cerr << "Unknown algorithm: " << algorithm << '\n';
    }
    
    cout << "DEBUG: handleTestMode completed\n";
}

int main(int argc, char* argv[]) {
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
            cerr << "Usage: ./main --file <algorithm> <inputFile>\n";
            return 1;
        }

        string algorithm = argv[2];
        string inputFile = argv[3];
        handleFileMode(algorithm, inputFile);
    } else if (mode == "--test") {
        if (argc < 5) {
            cerr << "Usage: ./main --test <algorithm> <size> <density>\n";
            return 1;
        }

        string algorithm = argv[2];
        int size = stoi(argv[3]);
        double density = stod(argv[4]);
        handleTestMode(algorithm, size, density);
    } else {
        cerr << "Unknown mode. Use --help for usage.\n";
        return 1;
    }

    cout << "DEBUG: Program ending normally\n";
    return 0;
}