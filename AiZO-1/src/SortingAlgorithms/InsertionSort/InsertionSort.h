#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "../../List/List.h"
#include "../../Vector/Vector.h"

template <typename T>
class InsertionSort {
public:
    InsertionSort() {}
    ~InsertionSort() {}

    void sort(List<T>& list);

private:
    void insertionSort(Vector<T>& arr);
};

#endif // INSERTIONSORT_H

#include "InsertionSort.tpp"
