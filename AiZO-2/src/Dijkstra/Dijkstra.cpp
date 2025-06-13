#include "Dijkstra.h"
#include <iostream>
#include <climits>

Dijkstra::Dijkstra(const Graph& graph) : graph(graph) {
    int V = graph.getVerticesNumber();
    parent = new int[V];
    distance = new int[V];
    visited = new bool[V];
}

Dijkstra::~Dijkstra() {
    delete[] parent;
    delete[] distance;
    delete[] visited;
}

void Dijkstra::dijkstraAdjacencyList(int start) {
    startingVertex = start;
    int V = graph.getVerticesNumber();

    MinHeap heap(graph);

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[startingVertex] = 0;
    heap.add(new Edge(0, startingVertex, 0));

    while (!heap.isEmpty()) {
        Edge vertex = heap.poll();
        int u = vertex.dst;

        if (visited[u]) continue;
        visited[u] = true;

        Edge* neighbor = graph.getAdjacencyList()[u].head;
        while (neighbor != graph.getNullEdge()) {
            if (!visited[neighbor->dst]) {
                relax(neighbor->src, neighbor->dst, neighbor->weight, heap);
            }
            neighbor = neighbor->next;
        }
    }

    print();
}

void Dijkstra::dijkstraAdjacencyMatrix(int start) {
    startingVertex = start;
    int V = graph.getVerticesNumber();

    MinHeap heap(graph);

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[startingVertex] = 0;
    heap.add(new Edge(0, startingVertex, 0));

    while (!heap.isEmpty()) {
        Edge vertex = heap.poll();
        int u = vertex.dst;

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            Edge* neighbor = graph.getAdjacencyMatrix()[u][v];
            if (neighbor != graph.getNullEdge() && !visited[neighbor->dst]) {
                relax(neighbor->src, neighbor->dst, neighbor->weight, heap);
            }
        }
    }

    print();
}

void Dijkstra::relax(int u, int v, int w, MinHeap& heap) {
    if (distance[u] != INT_MAX && distance[v] > distance[u] + w) {
        distance[v] = distance[u] + w;
        parent[v] = u;
        heap.add(new Edge(0, v, distance[v]));
    }
}

void Dijkstra::print() const {
    std::cout << "\nShortest Paths from Vertex " << startingVertex << ":\n";
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        if (distance[i] == INT_MAX) {
            std::cout << "Vertex " << i << ": unreachable\n";
            continue;
        }

        std::string path = std::to_string(i);
        int v = i;
        while (parent[v] != v) {
            path = std::to_string(parent[v]) + " -> " + path;
            v = parent[v];
        }
        std::cout << "Vertex " << i << ": " << path << " (Cost: " << distance[i] << ")\n";
    }
}
