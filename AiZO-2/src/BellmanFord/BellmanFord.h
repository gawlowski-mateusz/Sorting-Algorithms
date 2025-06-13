#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "../Graph/Graph.h"

class BellmanFord {
private:
    Graph graph;
    void print(int parent[], int distance[]);

public:
    explicit BellmanFord(const Graph& graph);

    void bellmanFordAdjacencyList(int startingVertex);
    void bellmanFordAdjacencyMatrix(int startingVertex);
};

#endif // BELLMANFORD_H
