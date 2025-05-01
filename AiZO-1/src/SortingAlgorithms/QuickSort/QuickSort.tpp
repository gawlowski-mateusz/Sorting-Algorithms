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
            // Handle invalid pivot position
            pivot = array[(left + right) / 2]; // Default to middle
            break;
    }

    int l = left;
    int r = right;

    while (true) {
        while (array[l] < pivot) ++l;
        while (array[r] > pivot) --r;

        if (l < r) {
            // Swap array[l] and array[r]
            T temp = array[l];
            array[l] = array[r];
            array[r] = temp;
            ++l;
            --r;
        } else {
            if (r == right) r--;
            return r;
        }
    }
}

template <typename T>
void QuickSort<T>::quickSort(Vector<T>& array, int left, int right, char pivot_position) {
    if (left >= right) return;

    int m = partition(array, left, right, pivot_position);

    quickSort(array, left, m, pivot_position);
    quickSort(array, m + 1, right, pivot_position);
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