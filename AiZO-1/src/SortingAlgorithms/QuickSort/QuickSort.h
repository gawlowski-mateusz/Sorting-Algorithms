#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../../List/List.h"

template <typename T>
class QuickSort {
public:
    QuickSort();
    ~QuickSort();

    void sort(List<T>& list, char pivot_position = 'm');  // 'l', 'm', 'r', 'x'

private:
    int partition(std::vector<T>& array, int left, int right, char pivot_position);
    void quickSort(std::vector<T>& array, int left, int right, char pivot_position);
};

#endif // QUICKSORT_H

#include "QuickSort.tpp"
