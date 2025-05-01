template <typename T>
void InsertionSort<T>::insertionSort(Vector<T>& arr) {
    int n = arr.getSize();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void InsertionSort<T>::sort(List<T>& list) {
    if (list.getSize() <= 1)
        return;

    Vector<T> values;
    Node<T>* current = list.getList();
    
    while (current) {
        values.pushBack(current->value);
        current = current->next;
    }

    insertionSort(values);

    list.clear(); // Clear the original list
    
    for (int i = 0; i < values.getSize(); i++) {
        list.insertAtTail(values[i]);
    }
}