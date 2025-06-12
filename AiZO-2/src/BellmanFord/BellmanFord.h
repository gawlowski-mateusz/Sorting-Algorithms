#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "../Graph/Graph.h"

template <typename T>
class BellmanFord {
private:
    Graph<T> graph;
    void print(int* parent, int* distance, int startingVertex);

public:
    BellmanFord(const Graph<T>& graph);

    void bellmanFordAdjacencyList(int startingVertex);
    void bellmanFordAdjacencyMatrix(int startingVertex);
};

#include "BellmanFord.tpp"

#endif // BELLMANFORD_H
