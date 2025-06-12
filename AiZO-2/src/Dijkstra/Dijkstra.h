#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../Graph/Graph.h"
#include "../MinHeap/MinHeap.h"

template <typename T>
class Dijkstra {
private:
    Graph<T> graph;
    int* parent;
    int* distance;
    bool* sptSet;
    int startingVertex;

    void relax(int u, int v, int weight, MinHeap<T>& heap);
    void print();

public:
    Dijkstra(const Graph<T>& graph);
    ~Dijkstra();

    void dijkstraAdjacencyList(int startingVertex);
    void dijkstraAdjacencyMatrix(int startingVertex);
};

#include "Dijkstra.tpp"

#endif // DIJKSTRA_H
