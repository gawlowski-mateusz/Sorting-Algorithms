#include <vector>
#include <cmath>

template<typename T>
ShellSort<T>::ShellSort() = default;

template<typename T>
ShellSort<T>::~ShellSort() = default;

template<typename T>
int ShellSort<T>::calculateK0(int size, int space_selector) const {
    int k = 0;
    switch (space_selector) {
        case 1:
            while ((pow(2, k) - 1) < size) ++k;
            return --k;
        case 2:
            while (ceil(1.8 * pow(2.25, k - 1) - 0.8) < size) ++k;
            return --k;
        default:
            return 0;
    }
}

template<typename T>
int ShellSort<T>::calculateGap(int k, int space_selector) const {
    switch (space_selector) {
        case 1:
            return static_cast<int>(pow(2, k) - 1); // Papernov-Stasevich
        case 2:
            return static_cast<int>(ceil(1.8 * pow(2.25, k - 1) - 0.8)); // Tokuda
        default:
            return 1;
    }
}

template<typename T>
void ShellSort<T>::shellSort(std::vector<T>& data, int space_selector) {
    int N = static_cast<int>(data.size());
    int k = calculateK0(N, space_selector);
    int gap = calculateGap(k--, space_selector);

    while (k >= 0) {
        for (int i = gap; i < N; i++) {
            T temp = data[i];
            int j = i;
            while (j >= gap && data[j - gap] > temp) {
                data[j] = data[j - gap];
                j -= gap;
            }
            data[j] = temp;
        }
        gap = calculateGap(k--, space_selector);
    }
}

template<typename T>
void ShellSort<T>::sort(List<T>& list, int space_selector) {
    if (list.getSize() <= 1) return;

    std::vector<T> values;
    Node<T>* current = list.getList();  // Returns copy

    while (current) {
        values.push_back(current->value);
        current = current->next;
    }

    shellSort(values, space_selector);

    current = list.getList();  // Refresh pointer
    for (const T& value : values) {
        current->value = value;
        current = current->next;
    }
}
