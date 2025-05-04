template <typename T>
int QuickSort<T>::partition(Vector<T>& array, int left, int right, char pivot_position) {
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
            pivot = array[(left + right) / 2];
            break;
    }

    int l = left - 1;
    int r = right + 1;

    while (true) {
        do { ++l; } while (array[l] < pivot);
        do { --r; } while (array[r] > pivot);

        if (l >= r)
            return r;

        // Swap array[l] and array[r]
        T temp = array[l];
        array[l] = array[r];
        array[r] = temp;
    }
}

template <typename T>
void QuickSort<T>::quickSort(Vector<T>& array, int left, int right, char pivot_position) {
    if (left < right) {
        int p = partition(array, left, right, pivot_position);
        quickSort(array, left, p, pivot_position);
        quickSort(array, p + 1, right, pivot_position);
    }
}

template <typename T>
void QuickSort<T>::sort(List<T>& list, char pivot_position) {
    if (list.getSize() <= 1)
        return;

    Vector<T> values;
    Node<T>* current = list.getList();
    
    while (current) {
        values.pushBack(current->value);
        current = current->next;
    }

    quickSort(values, 0, values.getSize() - 1, pivot_position);

    list.clear(); // Clear the original list
    
    for (int i = 0; i < values.getSize(); i++) {
        list.insertAtTail(values[i]);
    }
}