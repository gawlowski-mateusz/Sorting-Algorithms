// #include "InsertionSort.h"

template <typename T>
InsertionSort<T>::InsertionSort() = default;

template <typename T>
InsertionSort<T>::~InsertionSort() = default;

template <typename T>
void InsertionSort<T>::insertionSort(std::vector<T>& vec) {
    for (int i = 1; i < vec.size(); ++i) {
        T key = vec[i];
        int j = i;

        while (j > 0 && vec[j - 1] > key) {
            vec[j] = vec[j - 1];
            j--;
        }
        vec[j] = key;
    }
}

template <typename T>
void InsertionSort<T>::sort(List<T>& list) {
    if (list.getSize() <= 1) return;

    // Extract values from the list
    std::vector<T> values;
    Node<T>* current = list.getList();
    while (current) {
        values.push_back(current->value);
        Node<T>* temp = current;
        current = current->next;
        delete temp; // clean up
    }

    // Perform insertion sort
    insertionSort(values);

    // Copy sorted values back into the original list
    current = list.getList();  // re-copy to get original structure
    Node<T>* orig = list.getList();
    int index = 0;

    while (orig && index < values.size()) {
        orig->value = values[index++];
        orig = orig->next;
    }

    // Free temp copy again
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}