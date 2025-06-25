#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>
#include "../Graph/Graph.h"

class MinHeap {
private:
    static const int ARRAY_SIZE = 321000;
    Edge* array;
    Graph graph;
    int size;
    int left(int index);
    int right(int index);
    int parent(int index);

    void shiftUp(int index);
    void shiftDown(int index);

    void buildHeap();
    void initHeap();
    void removeElement(int index);

public:
    explicit MinHeap(Graph graph);
    ~MinHeap();

    void add(Edge* edge);
    void removeAll();
    bool isEmpty();
    int isInside(int value);
    Edge poll();

    void heapSort();
    void display(std::string sp, std::string sn, int v);

    void loadGraphFromAdjacencyList();
    void loadGraphFromAdjacencyMatrix();

    void setGraph(Graph graph);
    void loadFromFile(std::string filename, int structureSize);
    void saveToFile();
};

#endif // MINHEAP_H
