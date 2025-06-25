#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include "../Graph/Graph.h"

class FordFulkerson {
private:
    Graph graph;
    int lastMaxFlow = -1;

    bool bfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent);
    bool dfsAdjacencyMatrix(int** residualGraph, int start, int end, int* parent, bool* visited);
    void freeResidualGraph(int** residualGraph, int size);
    int** buildResidualMatrix();

public:
    explicit FordFulkerson(const Graph& graph);

    void fordFulkersonBFSAdjacencyMatrix(int start, int end);
    void fordFulkersonDFSAdjacencyMatrix(int start, int end);
    void saveToFile(const std::string& filename, const std::string& method) const;
};

#endif // FORDFULKERSON_H
