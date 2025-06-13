#include "Kruskal.h"
#include "../MinHeap/MinHeap.h"

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

Kruskal::Kruskal(Graph graph) : graph(graph) {
    int V = graph.getVerticesNumber();
    rank = new int[V];
    parent = new int[V];

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

Kruskal::~Kruskal() {
    delete[] parent;
    delete[] rank;
}

void Kruskal::init() {
    int V = graph.getVerticesNumber();
    delete[] parent;
    delete[] rank;

    parent = new int[V];
    rank = new int[V];

    for (int i = 0; i < V; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int Kruskal::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void Kruskal::Union(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

void Kruskal::kruskalAdjacencyList() {
    init();
    MinHeap heap(graph);
    heap.loadGraphFromAdjacencyList();

    int V = graph.getVerticesNumber();
    Edge* includedEdges = new Edge[V - 1];

    for (int i = 0; i < V - 1; ++i) {
        Edge edge = heap.poll();

        if (find(edge.src) != find(edge.dst)) {
            includedEdges[i] = edge;
            Union(edge.src, edge.dst);
        } else {
            i--;
        }
    }

    printMST(includedEdges);
    delete[] includedEdges;
}

void Kruskal::kruskalAdjacencyMatrix() {
    init();
    MinHeap heap(graph);
    heap.loadGraphFromAdjacencyMatrix();

    int V = graph.getVerticesNumber();
    Edge* includedEdges = new Edge[V - 1];

    for (int i = 0; i < V - 1; ++i) {
        Edge edge = heap.poll();

        if (find(edge.src) != find(edge.dst)) {
            includedEdges[i] = edge;
            Union(edge.src, edge.dst);
        } else {
            i--;
        }
    }

    printMST(includedEdges);
    delete[] includedEdges;
}

void Kruskal::printMST(Edge edgesIncluded[]) {
    std::printf("Src|Dst|Wght\n");

    int V = graph.getVerticesNumber();
    int totalWeight = 0;

    for (int i = 0; i < V - 1; ++i) {
        std::printf("  %d|  %d|   %d\n", edgesIncluded[i].src, edgesIncluded[i].dst, edgesIncluded[i].weight);
        totalWeight += edgesIncluded[i].weight;
    }

    cout << "Total Weight of MST: " << totalWeight << endl;
}
