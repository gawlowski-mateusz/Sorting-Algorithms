#ifndef GRAPH_H
#define GRAPH_H

#include <string>

struct Edge {
    int src;
    int dst;
    int weight;
    Edge* next;

    Edge(int src, int destination, int weight);
    Edge();
};

struct VertexList {
    Edge* head = nullptr;
};

class Graph {
private:
    void createGraph(int vertices);
    void addUndirectedEdge(int src, int dst, int weight);
    void addDirectedEdge(int src, int dst, int weight);
    void printMatrix();
    void printList();

    int numberOfVertices = 0;
    int numberOfEdges = 0;
    VertexList* AdjacencyList = nullptr;
    Edge*** AdjacencyMatrix;
    Edge* NULL_EDGE;

public:
    Graph();
    ~Graph();

    int loadFromFileMst(std::string fileName);
    int* loadFromFloat(std::string fileName);
    int loadFromSP(std::string fileName);

    void deleteEdge(int source, int destination);
    void deleteTest(Edge** e1, Edge** e2);

    void generateUndirectedGraph(int numberOfVertices, double density);
    void generateDirectedGraph(int numberOfVertices, double density);

    bool removeDirectedEdge(int src, int dst);
    bool removeUndirectedEdge(int src, int dst);

    void print();
    void deleteList();
    void deleteMatrix();
    void deleteGraph();

    // Getters
    int getVerticesNumber() const;
    int getEdgeNumber() const;
    VertexList* getAdjacencyList() const;
    Edge*** getAdjacencyMatrix() const;
    Edge* getNullEdge() const;
};

#endif // GRAPH_H