#include "Graph.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Edge Definitions
Edge::Edge(int src, int destination, int weight)
    : src(src), dst(destination), weight(weight % 32000), next(nullptr) {}

Edge::Edge() : src(0), dst(0), weight(0), next(nullptr) {}

// Graph Constructor
Graph::Graph() {
    NULL_EDGE = new Edge(0, 0, 0);
    AdjacencyList = nullptr;
    AdjacencyMatrix = nullptr;
}

Graph::~Graph() = default;

// Private Methods
void Graph::createGraph(int vertices) {
    NULL_EDGE = new Edge(0, 0, 0);
    numberOfVertices = vertices;
    AdjacencyList = new VertexList[vertices];
    for (int i = 0; i < vertices; ++i) {
        AdjacencyList[i].head = NULL_EDGE;
    }

    AdjacencyMatrix = new Edge**[vertices];
    for (int i = 0; i < vertices; ++i) {
        AdjacencyMatrix[i] = new Edge*[vertices];
        for (int j = 0; j < vertices; ++j) {
            AdjacencyMatrix[i][j] = NULL_EDGE;
        }
    }
}

void Graph::addUndirectedEdge(int src, int dst, int weight) {
    Edge* prevHead = AdjacencyList[src].head;
    AdjacencyList[src].head = new Edge(src, dst, weight);
    AdjacencyList[src].head->next = prevHead;

    prevHead = AdjacencyList[dst].head;
    AdjacencyList[dst].head = new Edge(dst, src, weight);
    AdjacencyList[dst].head->next = prevHead;

    AdjacencyMatrix[src][dst] = new Edge(src, dst, weight);
    AdjacencyMatrix[dst][src] = new Edge(dst, src, weight);
    numberOfEdges += 2;
}

void Graph::addDirectedEdge(int src, int dst, int weight) {
    Edge* prevHead = AdjacencyList[src].head;
    AdjacencyList[src].head = new Edge(src, dst, weight);
    AdjacencyList[src].head->next = prevHead;

    AdjacencyMatrix[src][dst] = new Edge(src, dst, weight);
    numberOfEdges += 1;
}

void Graph::printMatrix() {
    const int W = 4;

    std::cout << "\n    ";
    for (int i = 0; i < numberOfVertices; ++i)
        std::cout << std::setw(W) << i;
    std::cout << "\n";

    for (int i = 0; i < numberOfVertices; ++i) {
        std::cout << std::setw(2) << i << " |";
        for (int j = 0; j < numberOfVertices; ++j) {
            std::cout << std::setw(W) << AdjacencyMatrix[i][j]->weight;
        }
        std::cout << "\n";
    }
}

void Graph::printList() {
    for (int i = 0; i < numberOfVertices; ++i) {
        std::cout << std::setw(2) << i << " |";
        Edge* edge = AdjacencyList[i].head;
        while (edge != NULL_EDGE) {
            std::cout << " -> [" << std::setw(2) << edge->dst 
                      << ", " << std::setw(2) << edge->weight << "]";
            edge = edge->next;
        }
        std::cout << "\n";
    }
}

void Graph::print() {
    printList();
    printMatrix();
}

void Graph::deleteList() {
    for (int i = 0; i < numberOfVertices; ++i) {
        while (AdjacencyList[i].head != NULL_EDGE) {
            Edge* toDelete = AdjacencyList[i].head;
            AdjacencyList[i].head = toDelete->next;
            delete toDelete;
        }
    }
    delete[] AdjacencyList;
    AdjacencyList = nullptr;
}

void Graph::deleteMatrix() {
    for (int i = 0; i < numberOfVertices; ++i) {
        for (int j = 0; j < numberOfVertices; ++j) {
            if (AdjacencyMatrix[i][j] != NULL_EDGE)
                delete AdjacencyMatrix[i][j];
        }
    }
    delete[] AdjacencyMatrix;
    AdjacencyMatrix = nullptr;
}

void Graph::deleteGraph() {
    deleteList();
    deleteMatrix();
    numberOfVertices = 0;
    numberOfEdges = 0;
}

bool Graph::removeDirectedEdge(int src, int dst) {
    Edge* edge = AdjacencyList[src].head;
    Edge* prevEdge = edge;
    while (edge->dst != dst && edge != NULL_EDGE) {
        prevEdge = edge;
        edge = edge->next;
    }
    if (edge == NULL_EDGE) return false;
    prevEdge->next = edge->next;
    delete edge;

    delete AdjacencyMatrix[src][dst];
    AdjacencyMatrix[src][dst] = NULL_EDGE;
    numberOfEdges -= 1;
    return true;
}

bool Graph::removeUndirectedEdge(int src, int dst) {
    if (removeDirectedEdge(src, dst)) {
        removeDirectedEdge(dst, src);
        return true;
    }
    return false;
}

void Graph::generateUndirectedGraph(int numberOfVertices, double density) {
    createGraph(numberOfVertices);
    
    int maxPossibleEdges = (numberOfVertices * (numberOfVertices - 1)) / 2;
    int targetEdges = static_cast<int>(floor(maxPossibleEdges * density));
    int minEdgesForConnectivity = numberOfVertices - 1;
    
    if (targetEdges < minEdgesForConnectivity) {
        targetEdges = minEdgesForConnectivity;
    }
    
    int edgesAdded = 0;
    
    for (int i = 0; i < numberOfVertices - 1; ++i) {
        addUndirectedEdge(i, i + 1, rand() % 10 + 1);
        edgesAdded++;
    }
    
    int attempts = 0;
    int maxAttempts = targetEdges * 10;
    
    while (edgesAdded < targetEdges && attempts < maxAttempts) {
        int src = rand() % numberOfVertices;
        int dst = rand() % numberOfVertices;
        
        if (src == dst || AdjacencyMatrix[src][dst] != NULL_EDGE) {
            attempts++;
            continue;
        }
        
        addUndirectedEdge(src, dst, rand() % 20 + 1);
        edgesAdded++;
        attempts = 0;
    }
}

void Graph::generateDirectedGraph(int numberOfVertices, double density) {
    createGraph(numberOfVertices);
    
    int maxPossibleEdges = numberOfVertices * (numberOfVertices - 1);
    int targetEdges = static_cast<int>(floor(maxPossibleEdges * density));
    int minEdgesForPath = numberOfVertices - 1;
    
    if (targetEdges < minEdgesForPath) {
        targetEdges = minEdgesForPath;
    }
    
    int edgesAdded = 0;
    
    for (int i = 0; i < numberOfVertices - 1; ++i) {
        addDirectedEdge(i, i + 1, rand() % 10 + 1);
        edgesAdded++;
    }
    
    int attempts = 0;
    int maxAttempts = targetEdges * 10;
    
    while (edgesAdded < targetEdges && attempts < maxAttempts) {
        int src = rand() % numberOfVertices;
        int dst = rand() % numberOfVertices;
        
        if (src == dst || AdjacencyMatrix[src][dst] != NULL_EDGE) {
            attempts++;
            continue;
        }
        
        addDirectedEdge(src, dst, rand() % 20 + 1);
        edgesAdded++;
        attempts = 0;
    }
}

int Graph::loadFromFileMst(std::string fileName) {
    deleteGraph();
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Can not open file" << std::endl;
        return -1;
    }
    int edges;
    file >> edges >> numberOfVertices;
    createGraph(numberOfVertices);
    for (int i = 0; i < edges; ++i) {
        int src, dst, wght;
        file >> src >> dst >> wght;
        addUndirectedEdge(src, dst, wght);
    }
    file.close();
    return 0;
}

int* Graph::loadFromFloat(std::string fileName) {
    deleteGraph();
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Can not open file" << std::endl;
        return nullptr;
    }
    static int SandT[2];
    int edges, startVertex, endVertex;
    file >> edges >> numberOfVertices >> startVertex >> endVertex;
    createGraph(numberOfVertices);
    for (int i = 0; i < edges; ++i) {
        int src, dst, wght;
        file >> src >> dst >> wght;
        addDirectedEdge(src, dst, wght);
    }
    SandT[0] = startVertex;
    SandT[1] = endVertex;
    file.close();
    return SandT;
}

int Graph::loadFromSP(std::string fileName) {
    deleteGraph();
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Can not open file" << std::endl;
        return -1;
    }
    int edges, startingVertex;
    file >> edges >> numberOfVertices >> startingVertex;
    createGraph(numberOfVertices);
    for (int i = 0; i < edges; ++i) {
        int src, dst, wght;
        file >> src >> dst >> wght;
        addDirectedEdge(src, dst, wght);
    }
    file.close();
    return startingVertex;
}

// Getters
int Graph::getVerticesNumber() const { return numberOfVertices; }
int Graph::getEdgeNumber() const { return numberOfEdges; }
VertexList* Graph::getAdjacencyList() const { return AdjacencyList; }
Edge*** Graph::getAdjacencyMatrix() const { return AdjacencyMatrix; }
Edge* Graph::getNullEdge() const { return NULL_EDGE; }