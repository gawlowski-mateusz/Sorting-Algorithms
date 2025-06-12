#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../Graph/Graph.h"
#include "../MinHeap/MinHeap.h"
#include <vector>

template <typename T>
class Kruskal {
private:
    Graph<T> graph;
    int* rank;
    int* parent;

    void init();
    int find(int x);
    void Union(int x, int y);
    void printMST(const std::vector<Edge<T>>& edgesIncluded);

public:
    Kruskal(const Graph<T>& graph);
    ~Kruskal();

    void kruskalAdjacencyList();
    void kruskalAdjacencyMatrix();
};

#include "Kruskal.tpp"

#endif // KRUSKAL_H
