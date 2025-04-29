#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../../List/List.h"

template <typename T>
class HeapSort {
public:
    HeapSort();
    ~HeapSort();

    void sort(List<T>& list);

private:
    void buildHeap(std::vector<T>& vec);
    void siftDown(std::vector<T>& vec, int N, int i);

    int left(int index);
    int right(int index);
    int parent(int index);
};

#endif // HEAPSORT_H

#include "HeapSort.tpp"
