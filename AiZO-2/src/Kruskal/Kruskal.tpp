#include <iostream>
#include <stdexcept>

template <typename T>
Kruskal<T>::Kruskal(const Graph<T>& graph) : graph(graph) {
    rank = new int[graph.getVerticesNumber()];
    parent = new int[graph.getVerticesNumber()];
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

template <typename T>
Kruskal<T>::~Kruskal() {
    delete[] parent;
    delete[] rank;
}

template <typename T>
void Kruskal<T>::init() {
    delete[] parent;
    delete[] rank;
    parent = new int[graph.getVerticesNumber()];
    rank = new int[graph.getVerticesNumber()];

    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

template <typename T>
int Kruskal<T>::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

template <typename T>
void Kruskal<T>::Union(int x, int y) {
    int a = find(x);
    int b = find(y);
    if (rank[a] < rank[b])
        parent[a] = b;
    else if (rank[a] > rank[b])
        parent[b] = a;
    else {
        parent[b] = a;
        rank[a]++;
    }
}

template <typename T>
void Kruskal<T>::kruskalAdjacencyList() {
    init();
    MinHeap<T> heap(graph);
    heap.loadGraphFromAdjacencyList();

    std::vector<Edge<T>> includedEdges;
    while (includedEdges.size() < graph.getVerticesNumber() - 1) {
        Edge<T> edge = heap.poll();
        if (find(edge.source) != find(edge.destination)) {
            includedEdges.push_back(edge);
            Union(edge.source, edge.destination);
        }
    }

    printMST(includedEdges);
}

template <typename T>
void Kruskal<T>::kruskalAdjacencyMatrix() {
    init();
    MinHeap<T> heap(graph);
    heap.loadGraphFromAdjacencyMatrix();

    std::vector<Edge<T>> includedEdges;
    while (includedEdges.size() < graph.getVerticesNumber() - 1) {
        Edge<T> edge = heap.poll();
        if (find(edge.source) != find(edge.destination)) {
            includedEdges.push_back(edge);
            Union(edge.source, edge.destination);
        }
    }

    printMST(includedEdges);
}

template <typename T>
void Kruskal<T>::printMST(const std::vector<Edge<T>>& edgesIncluded) {
    std::printf("Src|Dst|Wght\n");
    int totalWeight = 0;
    for (const auto& edge : edgesIncluded) {
        std::printf("  %d|  %d|   %d\n", edge.source, edge.destination, edge.weight);
        totalWeight += edge.weight;
    }
    std::cout << "Total Weight: " << totalWeight << std::endl;
}
