#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>
#include "../Graph/Graph.h"

template <typename T>
class MinHeap {
private:
    Edge<T>* array;
    int size;
    Graph<T> graph;
    const static int ARRAY_SIZE = 1000;

    int left(int index);
    int right(int index);
    int parent(int index);
    void shiftUp(int i);
    void shiftDown(int i);

public:
    MinHeap(Graph<T> graph);
    ~MinHeap();

    void buildHeap();
    void add(Edge<T>* edge);
    void removeAll();
    void removeElement(int index);
    int isInside(int value);
    void display(std::string sp = "", std::string sn = "", int v = 0);
    void heapSort();
    void loadGraphFromAdjacencyList();
    void loadGraphFromAdjacencyMatrix();
    bool isEmpty();
    Edge<T> poll();
};

#include "MinHeap.tpp"

#endif // MINHEAP_H
