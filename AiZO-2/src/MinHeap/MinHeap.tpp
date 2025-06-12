#include <iostream>
#include <utility>

template <typename T>
MinHeap<T>::MinHeap(Graph<T> graph) {
    array = new Edge<T>[ARRAY_SIZE];
    size = 0;
    this->graph = graph;
}

template <typename T>
MinHeap<T>::~MinHeap() {
    if (size > 0) {
        delete[] array;
    }
}

template <typename T>
int MinHeap<T>::left(int index) {
    return 2 * index + 1;
}

template <typename T>
int MinHeap<T>::right(int index) {
    return 2 * index + 2;
}

template <typename T>
int MinHeap<T>::parent(int index) {
    return (index - 1) / 2;
}

template <typename T>
void MinHeap<T>::shiftUp(int i) {
    if (i == 0) return;
    if (array[i].weight < array[parent(i)].weight) {
        std::swap(array[i], array[parent(i)]);
        shiftUp(parent(i));
    }
}

template <typename T>
void MinHeap<T>::shiftDown(int i) {
    int smallest = i;
    int l = left(i);
    int r = right(i);

    if (l < size && array[l].weight < array[smallest].weight)
        smallest = l;

    if (r < size && array[r].weight < array[smallest].weight)
        smallest = r;

    if (smallest != i) {
        std::swap(array[i], array[smallest]);
        shiftDown(smallest);
    }
}

template <typename T>
void MinHeap<T>::buildHeap() {
    for (int i = (size / 2) - 1; i >= 0; --i)
        shiftDown(i);
}

template <typename T>
void MinHeap<T>::add(Edge<T>* edge) {
    if (size >= ARRAY_SIZE) return;
    array[size] = *edge;
    shiftUp(size);
    size++;
}

template <typename T>
void MinHeap<T>::removeAll() {
    size = 0;
}

template <typename T>
void MinHeap<T>::removeElement(int index) {
    array[index] = array[size - 1];
    size--;
    shiftUp(index);
    shiftDown(index);
}

template <typename T>
int MinHeap<T>::isInside(int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i].weight == value)
            return i;
    }
    return -1;
}

template <typename T>
void MinHeap<T>::display(std::string sp, std::string sn, int v) {
    std::string s, cr = "┌─", cl = "└─", cp = "│ ";
    if (v < size) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        display(s + cp, cr, right(v));

        s = s.substr(0, sp.length() - 2);
        std::cout << s << sn << array[v].weight << std::endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        display(s + cp, cl, left(v));
    }
}

template <typename T>
void MinHeap<T>::heapSort() {
    int originalSize = size;
    for (int i = size - 1; i >= 0; --i) {
        std::swap(array[0], array[i]);
        size--;
        shiftDown(0);
    }
    size = originalSize;
}

template <typename T>
void MinHeap<T>::loadGraphFromAdjacencyList() {
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        Edge<T>* edge = graph.getAdjacencyList()[i].head;
        while (edge != graph.getNullEdge()) {
            add(edge);
            edge = edge->next;
        }
    }
}

template <typename T>
void MinHeap<T>::loadGraphFromAdjacencyMatrix() {
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        for (int j = 0; j < graph.getVerticesNumber(); ++j) {
            Edge<T>* edge = graph.getAdjacencyMatrix()[i][j];
            if (edge == graph.getNullEdge()) continue;
            add(edge);
        }
    }
}

template <typename T>
bool MinHeap<T>::isEmpty() {
    return size == 0;
}

template <typename T>
Edge<T> MinHeap<T>::poll() {
    Edge<T> top = array[0];
    removeElement(0);
    return top;
}
