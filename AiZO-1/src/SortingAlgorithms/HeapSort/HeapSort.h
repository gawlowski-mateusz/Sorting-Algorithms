#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../../List/List.h"
#include "../../Vector/Vector.h"

template <typename T>
class HeapSort {
public:
    HeapSort() {}
    ~HeapSort() {}

    void sort(List<T>& list);

private:
    void heapify(Vector<T>& arr, int n, int i);
};

#endif // HEAPSORT_H

#include "HeapSort.tpp"
