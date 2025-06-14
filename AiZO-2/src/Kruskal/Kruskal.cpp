#include <iostream>
#include <iomanip>
#include <cstdio>
#include "Kruskal.h"
#include "../MinHeap/MinHeap.h"


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
    std::cout << "Minimum Spanning Tree Edges:\n";
    std::cout << std::setw(5) << "Src" 
              << std::setw(6) << "Dst" 
              << std::setw(9) << "Weight\n";
    std::cout << "---------------------------\n";

    int totalWeight = 0;
    int V = graph.getVerticesNumber();

    for (int i = 0; i < V - 1; ++i) {
        std::cout << std::setw(5) << edgesIncluded[i].src
                  << std::setw(6) << edgesIncluded[i].dst
                  << std::setw(8) << edgesIncluded[i].weight << "\n";
        totalWeight += edgesIncluded[i].weight;
    }

    std::cout << "---------------------------\n";
    std::cout << "Total Weight of MST: " << totalWeight << "\n";
}
