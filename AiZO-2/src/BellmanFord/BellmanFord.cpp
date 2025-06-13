#include "BellmanFord.h"
#include <iostream>
#include <climits>

BellmanFord::BellmanFord(const Graph& graph) : graph(graph) {}

void BellmanFord::bellmanFordAdjacencyList(int startingVertex) {
    int V = graph.getVerticesNumber();
    int* distance = new int[V];
    int* parent = new int[V];

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
    }
    distance[startingVertex] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            Edge* edge = graph.getAdjacencyList()[j].head;
            while (edge != graph.getNullEdge()) {
                int u = edge->src;
                int v = edge->dst;
                int w = edge->weight;
                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }
                edge = edge->next;
            }
        }
    }

    // Negative cycle check
    for (int j = 0; j < V; ++j) {
        Edge* edge = graph.getAdjacencyList()[j].head;
        while (edge != graph.getNullEdge()) {
            int u = edge->src;
            int v = edge->dst;
            int w = edge->weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                std::cout << "Negative weight cycle detected!\n";
                delete[] distance;
                delete[] parent;
                return;
            }
            edge = edge->next;
        }
    }

    print(parent, distance);
    delete[] distance;
    delete[] parent;
}

void BellmanFord::bellmanFordAdjacencyMatrix(int startingVertex) {
    int V = graph.getVerticesNumber();
    int* distance = new int[V];
    int* parent = new int[V];

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
    }
    distance[startingVertex] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < V; ++j) {
            for (int k = 0; k < V; ++k) {
                Edge* edge = graph.getAdjacencyMatrix()[j][k];
                if (edge == graph.getNullEdge()) continue;
                int u = edge->src;
                int v = edge->dst;
                int w = edge->weight;
                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    // Negative cycle check
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            Edge* edge = graph.getAdjacencyMatrix()[i][j];
            if (edge == graph.getNullEdge()) continue;
            int u = edge->src;
            int v = edge->dst;
            int w = edge->weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                std::cout << "Negative weight cycle detected!\n";
                delete[] distance;
                delete[] parent;
                return;
            }
        }
    }

    print(parent, distance);
    delete[] distance;
    delete[] parent;
}

void BellmanFord::print(int parent[], int distance[]) {
    std::cout << "\nShortest Paths:\n";
    int V = graph.getVerticesNumber();
    for (int i = 0; i < V; ++i) {
        if (distance[i] == INT_MAX) {
            std::cout << "Vertex " << i << ": unreachable\n";
            continue;
        }

        std::cout << "Vertex " << i << " (cost " << distance[i] << "): ";
        std::string path = std::to_string(i);
        int v = i;
        while (parent[v] != v) {
            path = std::to_string(parent[v]) + " -> " + path;
            v = parent[v];
        }
        std::cout << path << "\n";
    }
}
