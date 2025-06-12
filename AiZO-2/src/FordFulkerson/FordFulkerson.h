#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include "../Graph/Graph.h"

template <typename T>
class FordFulkerson {
private:
    Graph<T> graph;
    bool bfsAdjacencyMatrix(int** residualGraph, int startVertex, int endVertex, int parent[]);
    bool dfsAdjacencyMatrix(int** residualGraph, int startVertex, int endVertex, int parent[], bool* visited = nullptr);

public:
    explicit FordFulkerson(const Graph<T>& graph);

    void fordFulkersonBFSAdjacencyMatrix(int startVertex, int endVertex);
    void fordFulkersonDFSAdjacencyMatrix(int startVertex, int endVertex);
};

#include "FordFulkerson.tpp"

#endif // FORDFULKERSON_H
