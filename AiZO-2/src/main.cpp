#include <iostream>
#include <fstream>
#include <string>
#include "./Graph/Graph.h"
#include "./FordFulkerson/FordFulkerson.h"
#include "./Dijkstra/Dijkstra.h"
#include "./BellmanFord/BellmanFord.h"
#include "./Kruskal/Kruskal.h"

void printHelp() {
    std::cout << "\nUsage:\n"
              << "./main --file <algorithm> <inputFile>\n"
              << "./main --test <algorithm> <size> <density>\n"
              << "./main --help\n\n"
              << "Arguments:\n"
              << "  <algorithm>   ford-bfs | ford-dfs | dijkstra | bellman-ford | kruskal\n"
              << "  <inputFile>   Path to graph file\n"
              << "  <size>        Number of vertices\n"
              << "  <density>     Edge density (0.0 to 1.0)\n\n"
              << "Examples:\n"
              << "  ./main --file dijkstra ./input.txt\n"
              << "  ./main --test ford-bfs 10 0.6\n";
}

void handleFileMode(const std::string& algorithm, const std::string& inputFile) {
    Graph<int> graph;   // or float/double depending on your usage;

    if (graph.loadFromFileMst(inputFile) != 0) {
        std::cerr << "Failed to load graph from file: " << inputFile << '\n';
        return;
    }

    int start = 0;
    int end = graph.getVerticesNumber() - 1;

    if (algorithm == "ford-bfs") {
        FordFulkerson solver(graph);
        solver.fordFulkersonBFSAdjacencyMatrix(start, end);
    } else if (algorithm == "ford-dfs") {
        FordFulkerson solver(graph);
        solver.fordFulkersonDFSAdjacencyMatrix(start, end);
    } else if (algorithm == "dijkstra") {
        Dijkstra solver(graph);
        solver.dijkstraAdjacencyMatrix(start);
    } else if (algorithm == "bellman-ford") {
        BellmanFord solver(graph);
        solver.bellmanFordAdjacencyMatrix(start);
    } else if (algorithm == "kruskal") {
        Kruskal solver(graph);
        solver.kruskalAdjacencyMatrix();
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << '\n';
    }
}

void handleTestMode(const std::string& algorithm, int size, double density) {
    if (density < 0.0 || density > 1.0) {
        std::cerr << "Density must be between 0 and 1.\n";
        return;
    }

    Graph<int> graph;
    bool directed = (algorithm.find("ford") != std::string::npos); // Only Ford-Fulkerson needs directed graph
    graph.generateDirectedGraph(size, density);

    int start = 0;
    int end = size - 1;

    if (algorithm == "ford-bfs") {
        FordFulkerson solver(graph);
        solver.fordFulkersonBFSAdjacencyMatrix(start, end);
    } else if (algorithm == "ford-dfs") {
        FordFulkerson solver(graph);
        solver.fordFulkersonDFSAdjacencyMatrix(start, end);
    } else if (algorithm == "dijkstra") {
        Dijkstra solver(graph);
        solver.dijkstraAdjacencyList(start);
    } else if (algorithm == "bellman-ford") {
        BellmanFord solver(graph);
        solver.bellmanFordAdjacencyList(start);
    } else if (algorithm == "kruskal") {
        Kruskal solver(graph);
        solver.kruskalAdjacencyList();
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use --help for usage.\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "--help") {
        printHelp();
        return 0;
    } else if (mode == "--file") {
        if (argc < 4) {
            std::cerr << "Usage: ./main --file <algorithm> <inputFile>\n";
            return 1;
        }

        std::string algorithm = argv[2];
        std::string inputFile = argv[3];
        handleFileMode(algorithm, inputFile);
    } else if (mode == "--test") {
        if (argc < 5) {
            std::cerr << "Usage: ./main --test <algorithm> <size> <density>\n";
            return 1;
        }

        std::string algorithm = argv[2];
        int size = std::stoi(argv[3]);
        double density = std::stod(argv[4]);
        handleTestMode(algorithm, size, density);
    } else {
        std::cerr << "Unknown mode. Use --help for usage.\n";
        return 1;
    }

    return 0;
}
