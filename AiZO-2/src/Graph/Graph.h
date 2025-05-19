#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

template <typename T>
class Edge;

template <typename T>
class VertexList;

template <typename T>
class Edge {
public:
    int source;
    int destination;
    T weight;
    Edge<T>* next;

    Edge(int src, int dst, T wgt) : 
        source(src),
        destination(dst),
        weight(wgt),
        next(nullptr) {}
    
    Edge() : source(0), destination(0), weight(0), next(nullptr) {}
};

template <typename T>
class VertexList {
public:
    Edge<T>* head;
    
    VertexList() : head(nullptr) {}
};

template <typename T>
class Graph {
private:
    int vertices_number;
    int edge_number;
    VertexList<T>* adjacency_list;
    Edge<T>*** adjacency_matrix;
    Edge<T>* NULL_EDGE;

    // Helper methods
    void createGraph(int vertices);
    void printMatrix();
    void printList();

public:
    // Constructor and destructor
    Graph();
    ~Graph();

    // Edge manipulation methods
    void addUndirectedEdge(int src, int dst, T weight);
    void addDirectedEdge(int src, int dst, T weight);
    bool removeDirectedEdge(int src, int dst);
    bool removeUndirectedEdge(int src, int dst);

    // Graph generation methods
    void generateUndirectedGraph(int numberOfVertices, int density);
    void generateDirectedGraph(int numberOfVertices, int density);

    // Utility methods
    void print();
    void deleteList();
    void deleteMatrix();
    void deleteGraph();

    // File operations
    void loadFromFileMst(const std::string& fileName);
    int* loadFromFloat(const std::string& fileName);
    int loadFromSP(const std::string& fileName);
    
    // Getters
    int getVerticesNumber() const { return vertices_number; }
    int getEdgeNumber() const { return edge_number; }
};

#include "Graph.tpp"

#endif // GRAPH_H