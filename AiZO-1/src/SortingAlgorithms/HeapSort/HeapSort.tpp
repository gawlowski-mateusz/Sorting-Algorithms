template <typename T>
void HeapSort<T>::heapify(Vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        T temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

template <typename T>
void HeapSort<T>::sort(List<T>& list) {
    if (list.getSize() <= 1)
        return;

    Vector<T> values;    
    Node<T>* current = list.getList();
    
    while (current) {
        values.pushBack(current->value);
        current = current->next;
    }

    int n = values.getSize();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(values, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        T temp = values[0];
        values[0] = values[i];
        values[i] = temp;
        
        // Call max heapify on the reduced heap
        heapify(values, i, 0);
    }

    list.clear(); // Clear the original list
    
    for (int i = 0; i < values.getSize(); i++) {
        list.insertAtTail(values[i]);
    }
}