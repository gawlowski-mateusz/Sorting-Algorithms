#include <iostream>
#include <climits>
#include "../Queue/Queue.h"
#include "../Stack/Stack.h"

template <typename T>
FordFulkerson<T>::FordFulkerson(const Graph<T>& graph) : graph(graph) {}

template <typename T>
void FordFulkerson<T>::fordFulkersonBFSAdjacencyMatrix(int startVertex, int endVertex) {
    int V = graph.getVerticesNumber();
    int** rGraph = new int*[V];
    for (int i = 0; i < V; ++i)
        rGraph[i] = new int[V];

    for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
        rGraph[i][j] = graph.getAdjacencyMatrix()[i][j] ? graph.getAdjacencyMatrix()[i][j]->weight : 0;

    int* parent = new int[V];
    int max_flow = 0;

    while (bfsAdjacencyMatrix(rGraph, startVertex, endVertex, parent)) {
        int path_flow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v])
            path_flow = std::min(path_flow, rGraph[parent[v]][v]);

        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    std::cout << "Max flow (BFS): " << max_flow << std::endl;

    for (int i = 0; i < V; ++i) delete[] rGraph[i];
    delete[] rGraph;
    delete[] parent;
}

template <typename T>
void FordFulkerson<T>::fordFulkersonDFSAdjacencyMatrix(int startVertex, int endVertex) {
    int V = graph.getVerticesNumber();
    int** rGraph = new int*[V];
    for (int i = 0; i < V; ++i)
        rGraph[i] = new int[V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            rGraph[i][j] = graph.getAdjacencyMatrix()[i][j] ? graph.getAdjacencyMatrix()[i][j]->weight : 0;

    int* parent = new int[V];
    int max_flow = 0;

    while (dfsAdjacencyMatrix(rGraph, startVertex, endVertex, parent)) {
        int path_flow = INT_MAX;
        for (int v = endVertex; v != startVertex; v = parent[v])
            path_flow = std::min(path_flow, rGraph[parent[v]][v]);

        for (int v = endVertex; v != startVertex; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    std::cout << "Max flow (DFS): " << max_flow << std::endl;

    for (int i = 0; i < V; ++i) delete[] rGraph[i];
    delete[] rGraph;
    delete[] parent;
}

template <typename T>
bool FordFulkerson<T>::bfsAdjacencyMatrix(int** residualGraph, int startVertex, int endVertex, int parent[]) {
    int V = graph.getVerticesNumber();
    bool* visited = new bool[V]();

    Queue<int> queue;
    queue.push(startVertex);
    visited[startVertex] = true;
    parent[startVertex] = -1;

    while (!queue.isEmpty()) {
        int u = queue.pop();
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                if (v == endVertex) {
                    delete[] visited;
                    return true;
                }
                visited[v] = true;
                queue.push(v);
            }
        }
    }

    delete[] visited;
    return false;
}

template <typename T>
bool FordFulkerson<T>::dfsAdjacencyMatrix(int** residualGraph, int startVertex, int endVertex, int parent[], bool* visited) {
    int V = graph.getVerticesNumber();
    bool allocated = false;

    if (!visited) {
        visited = new bool[V]();
        allocated = true;
        parent[startVertex] = -1;
    }

    Stack<int> stack;
    stack.push(startVertex);
    visited[startVertex] = true;

    while (!stack.isEmpty()) {
        int u = stack.pop();
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                if (v == endVertex) {
                    if (allocated) delete[] visited;
                    return true;
                }
                visited[v] = true;
                stack.push(v);
            }
        }
    }

    if (allocated) delete[] visited;
    return false;
}
