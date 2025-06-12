#include <iostream>
#include <climits>
#include <string>

template <typename T>
BellmanFord<T>::BellmanFord(const Graph<T>& graph) : graph(graph) {}

template <typename T>
void BellmanFord<T>::bellmanFordAdjacencyList(int startingVertex) {
    int V = graph.getVerticesNumber();
    int* distance = new int[V];
    int* parent = new int[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        parent[i] = i;
    }

    distance[startingVertex] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            Edge<T>* edge = graph.getAdjacencyList()[j].head;
            while (edge != graph.getNullEdge()) {
                int u = edge->source;
                int v = edge->destination;
                int w = edge->weight;

                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }

                edge = edge->next;
            }
        }
    }

    // Negative cycle detection
    for (int j = 0; j < V; ++j) {
        Edge<T>* edge = graph.getAdjacencyList()[j].head;
        while (edge != graph.getNullEdge()) {
            int u = edge->source;
            int v = edge->destination;
            int w = edge->weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                std::cout << "Wykryto ujemny cykl!" << std::endl;
                delete[] parent;
                delete[] distance;
                return;
            }

            edge = edge->next;
        }
    }

    print(parent, distance, startingVertex);

    delete[] parent;
    delete[] distance;
}

template <typename T>
void BellmanFord<T>::bellmanFordAdjacencyMatrix(int startingVertex) {
    int V = graph.getVerticesNumber();
    int* distance = new int[V];
    int* parent = new int[V];

    for (int i = 0; i < V; ++i) {
        distance[i] = INT_MAX;
        parent[i] = i;
    }

    distance[startingVertex] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            for (int k = 0; k < V; ++k) {
                Edge<T>* edge = graph.getAdjacencyMatrix()[j][k];
                if (edge == graph.getNullEdge())
                    continue;

                int u = edge->source;
                int v = edge->destination;
                int w = edge->weight;

                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    // Negative cycle detection
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            Edge<T>* edge = graph.getAdjacencyMatrix()[i][j];
            if (edge == graph.getNullEdge())
                continue;

            int u = edge->source;
            int v = edge->destination;
            int w = edge->weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                std::cout << "Wykryto ujemny cykl!" << std::endl;
                delete[] parent;
                delete[] distance;
                return;
            }
        }
    }

    print(parent, distance, startingVertex);

    delete[] parent;
    delete[] distance;
}

template <typename T>
void BellmanFord<T>::print(int* parent, int* distance, int startingVertex) {
    std::cout << "\nŚcieżki od wierzchołka " << startingVertex << ":\n";
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        if (i == startingVertex) continue;

        std::string path = std::to_string(i);
        int vertex = i;

        while (parent[vertex] != vertex) {
            path = std::to_string(parent[vertex]) + "->" + path;
            vertex = parent[vertex];
        }

        std::cout << path << "  Dystans: " << distance[i] << std::endl;
    }
}
