#include "FordFulkerson.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include <fstream>
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

using std::cout;
using std::endl;
using std::min;

FordFulkerson::FordFulkerson(const Graph& graph) : graph(graph) {}

int** FordFulkerson::buildResidualMatrix() {
    int V = graph.getVerticesNumber();
    int** rGraph = new int*[V];
    for (int i = 0; i < V; ++i)
        rGraph[i] = new int[V];

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            rGraph[i][j] = graph.getAdjacencyMatrix()[i][j]->weight;

    return rGraph;
}

void FordFulkerson::freeResidualGraph(int** residualGraph, int size) {
    for (int i = 0; i < size; ++i)
        delete[] residualGraph[i];
    delete[] residualGraph;
}

void FordFulkerson::fordFulkersonBFSAdjacencyMatrix(int start, int end) {
    int V = graph.getVerticesNumber();
    int** rGraph = buildResidualMatrix();
    int* parent = new int[V];

    int maxFlow = 0;

    while (bfsAdjacencyMatrix(rGraph, start, end, parent)) {
        int pathFlow = INT_MAX;
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "Max Flow (BFS): " << maxFlow << endl;

    delete[] parent;
    freeResidualGraph(rGraph, V);
}

void FordFulkerson::fordFulkersonDFSAdjacencyMatrix(int start, int end) {
    int V = graph.getVerticesNumber();
    int** rGraph = buildResidualMatrix();
    int* parent = new int[V];
    bool* visited = new bool[V];

    int maxFlow = 0;

    while (dfsAdjacencyMatrix(rGraph, start, end, parent, visited)) {
        int pathFlow = INT_MAX;
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "Max Flow (DFS): " << maxFlow << endl;

    delete[] parent;
    delete[] visited;
    freeResidualGraph(rGraph, V);
}

bool FordFulkerson::bfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent) {
    int V = graph.getVerticesNumber();
    bool* visited = new bool[V]();
    Queue queue;

    queue.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!queue.isEmpty()) {
        int u = queue.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == end) {
                    delete[] visited;
                    return true;
                }
                queue.push(v);
            }
        }
    }

    delete[] visited;
    return false;
}

bool FordFulkerson::dfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent, bool* visitedExternal) {
    int V = graph.getVerticesNumber();
    bool* visited = visitedExternal;
    if (!visitedExternal) {
        visited = new bool[V]();
        parent[start] = -1;
    }

    Stack stack;
    stack.push(start);
    visited[start] = true;

    while (!stack.isEmpty()) {
        int u = stack.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;

                if (v == end) {
                    if (!visitedExternal) delete[] visited;
                    return true;
                }

                stack.push(v);
            }
        }
    }

    if (!visitedExternal) delete[] visited;
    return false;
}

void FordFulkerson::saveToFile(const std::string& filename, const std::string& method) const {
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    out << "Max Flow (" << method << "): " << lastMaxFlow << "\n";
    out.close();
}
