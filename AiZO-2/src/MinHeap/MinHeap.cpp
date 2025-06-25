#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::swap;

MinHeap::MinHeap(Graph graph) : graph(graph), size(0) {
    array = new Edge[ARRAY_SIZE];
}

MinHeap::~MinHeap() {
    delete[] array;
}

int MinHeap::left(int index) {
    return 2 * index + 1;
}

int MinHeap::right(int index) {
    return 2 * index + 2;
}

int MinHeap::parent(int index) {
    return (index - 1) / 2;
}

void MinHeap::shiftUp(int i) {
    while (i != 0 && array[i].weight < array[parent(i)].weight) {
        swap(array[i], array[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::shiftDown(int i) {
    int smallest = i;
    int l = left(i);
    int r = right(i);

    if (l < size && array[l].weight < array[smallest].weight)
        smallest = l;

    if (r < size && array[r].weight < array[smallest].weight)
        smallest = r;

    if (smallest != i) {
        swap(array[i], array[smallest]);
        shiftDown(smallest);
    }
}

void MinHeap::buildHeap() {
    for (int i = (size / 2) - 1; i >= 0; --i) {
        shiftDown(i);
    }
}

void MinHeap::add(Edge* edge) {
    array[size] = *edge;
    shiftUp(size);
    size++;
}

void MinHeap::removeAll() {
    size = 0;
}

void MinHeap::removeElement(int index) {
    array[index] = array[size - 1];
    size--;
    shiftUp(index);
    shiftDown(index);
}

int MinHeap::isInside(int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i].weight == value)
            return i;
    }
    return -1;
}

bool MinHeap::isEmpty() {
    return size == 0;
}

Edge MinHeap::poll() {
    Edge edge = array[0];
    removeElement(0);
    return edge;
}

void MinHeap::heapSort() {
    for (int i = size - 1; i >= 0; --i) {
        swap(array[0], array[i]);
        size--;
        shiftDown(0);
    }
}

void MinHeap::display(std::string sp, std::string sn, int v) {
    std::string cr = "┌─", cl = "└─", cp = "│ ";
    std::string s;

    if (v < size) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        display(s + cp, cr, right(v));

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << array[v].weight << endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        display(s + cp, cl, left(v));
    }
}

void MinHeap::loadGraphFromAdjacencyList() {
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        Edge* edge = graph.getAdjacencyList()[i].head;
        while (edge != graph.getNullEdge()) {
            add(edge);
            edge = edge->next;
        }
    }
}

void MinHeap::loadGraphFromAdjacencyMatrix() {
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        for (int j = 0; j < graph.getVerticesNumber(); ++j) {
            Edge* edge = graph.getAdjacencyMatrix()[i][j];
            if (edge != graph.getNullEdge()) {
                add(edge);
            }
        }
    }
}

void MinHeap::setGraph(Graph graph) {
    this->graph = graph;
}

// Placeholder methods if needed
void MinHeap::loadFromFile(std::string filename, int structureSize) {
    (void)filename;
    (void)structureSize;
}

void MinHeap::saveToFile() {
    // Not implemented
}
