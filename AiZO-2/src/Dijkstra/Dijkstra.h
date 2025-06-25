#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../Graph/Graph.h"
#include "../MinHeap/MinHeap.h"

class Dijkstra {
private:
    Graph graph;
    int* parent;
    int* distance;
    bool* visited;
    int startingVertex;

    void relax(int u, int v, int w, MinHeap& heap);
    void print() const;

public:
    explicit Dijkstra(const Graph& graph);
    ~Dijkstra();

    void dijkstraAdjacencyList(int start);
    void dijkstraAdjacencyMatrix(int start);
    void saveToFile(const std::string& filename) const;
};

#endif // DIJKSTRA_H
