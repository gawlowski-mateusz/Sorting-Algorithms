#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "../../List/List.h"

template<typename T>
class ShellSort {
public:
    ShellSort();
    ~ShellSort();

    void sort(List<T>& list, int space_selector = 1); // 1: Papernov-Stasevich, 2: Tokuda

private:
    int calculateK0(int size, int space_selector) const;
    int calculateGap(int k, int space_selector) const;
    void shellSort(std::vector<T>& data, int space_selector);
};

#endif // SHELLSORT_H

#include "ShellSort.tpp"
