#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../Graph/Graph.h"

class Kruskal {
private:
    Graph graph;
    int* parent;
    int* rank;

    void init();
    int find(int x);
    void Union(int x, int y);
    void printMST(Edge edgesIncluded[]);

public:
    explicit Kruskal(Graph graph);
    ~Kruskal();

    void kruskalAdjacencyList();
    void kruskalAdjacencyMatrix();
};

#endif // KRUSKAL_H
