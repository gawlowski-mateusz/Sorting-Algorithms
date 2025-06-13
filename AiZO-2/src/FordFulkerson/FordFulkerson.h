#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include "../Graph/Graph.h"

class FordFulkerson {
private:
    Graph graph;

    bool bfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent);
    bool dfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent, bool* visited);
    void freeResidualGraph(int** residualGraph, int size);
    int** buildResidualMatrix();

public:
    explicit FordFulkerson(const Graph& graph);

    void fordFulkersonBFSAdjacencyMatrix(int start, int end);
    void fordFulkersonDFSAdjacencyMatrix(int start, int end);
};

#endif // FORDFULKERSON_H
