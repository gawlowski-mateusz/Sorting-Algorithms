#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../../List/List.h"
#include "../../Vector/Vector.h"
#include "../../RandomGenerator/RandomGenerator.h"

template <typename T>
class QuickSort {
public:
    QuickSort() {}
    ~QuickSort() {}

    void sort(List<T>& list, char pivot_position = 'm');  // 'l', 'm', 'r', 'x'

private:
    int partition(Vector<T>& array, int left, int right, char pivot_position);
    void quickSort(Vector<T>& array, int left, int right, char pivot_position);
};

#endif // QUICKSORT_H

#include "QuickSort.tpp"
