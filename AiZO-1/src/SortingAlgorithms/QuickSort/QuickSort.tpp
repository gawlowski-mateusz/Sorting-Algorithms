#include "../../RandomGenerator/RandomGenerator.h"
#include <iostream>
#include <vector>

template <typename T>
QuickSort<T>::QuickSort() = default;

template <typename T>
QuickSort<T>::~QuickSort() = default;

template <typename T>
int QuickSort<T>::partition(std::vector<T>& array, int left, int right, char pivot_position) {
    T pivot;
    RandomGenerator rng;

    switch (pivot_position) {
        case 'l':
            pivot = array[left];
            break;
        case 'm':
            pivot = array[(left + right) / 2];
            break;
        case 'r':
            pivot = array[right];
            break;
        case 'x':
            pivot = array[rng.getInt() % (right - left + 1) + left];
            break;
        default:
            std::cout << "ERROR: invalid pivot position" << std::endl;
            exit(-1);
    }

    int l = left;
    int r = right;

    while (true) {
        while (array[l] < pivot) ++l;
        while (array[r] > pivot) --r;

        if (l < r) {
            std::swap(array[l], array[r]);
            ++l;
            --r;
        } else {
            if (r == right) r--;
            return r;
        }
    }
}

template <typename T>
void QuickSort<T>::quickSort(std::vector<T>& array, int left, int right, char pivot_position) {
    if (left >= right) return;

    int m = partition(array, left, right, pivot_position);

    quickSort(array, left, m, pivot_position);
    quickSort(array, m + 1, right, pivot_position);
}

template <typename T>
void QuickSort<T>::sort(List<T>& list, char pivot_position) {
    if (list.getSize() <= 1) return;

    std::vector<T> values;
    Node<T>* current = list.getList();  // Returns a *copy*

    while (current) {
        values.push_back(current->value);
        current = current->next;
    }

    quickSort(values, 0, static_cast<int>(values.size()) - 1, pivot_position);

    current = list.getList();
    for (const T& value : values) {
        current->value = value;
        current = current->next;
    }
}