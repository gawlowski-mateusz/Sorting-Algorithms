#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "../../List/List.h"

template <typename T>
class InsertionSort {
public:
    InsertionSort();
    ~InsertionSort();

    void sort(List<T>& list);

private:
    void insertionSort(std::vector<T>& vec);
};

#endif // INSERTIONSORT_H

#include "InsertionSort.tpp"
