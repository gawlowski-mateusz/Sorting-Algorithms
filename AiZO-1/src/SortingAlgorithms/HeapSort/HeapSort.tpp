template <typename T>
HeapSort<T>::HeapSort() = default;

template <typename T>
HeapSort<T>::~HeapSort() = default;

template <typename T>
int HeapSort<T>::left(int index) {
    return 2 * index + 1;
}

template <typename T>
int HeapSort<T>::right(int index) {
    return 2 * index + 2;
}

template <typename T>
int HeapSort<T>::parent(int index) {
    return (index - 1) / 2;
}

template <typename T>
void HeapSort<T>::siftDown(std::vector<T>& vec, int N, int i) {
    int largest = i;
    int l = left(i);
    int r = right(i);

    if (l < N && vec[l] > vec[largest])
        largest = l;
    if (r < N && vec[r] > vec[largest])
        largest = r;

    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        siftDown(vec, N, largest);
    }
}

template <typename T>
void HeapSort<T>::buildHeap(std::vector<T>& vec) {
    int startIdx = (vec.size() / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        siftDown(vec, vec.size(), i);
    }
}

template <typename T>
void HeapSort<T>::sort(List<T>& list) {
    if (list.getSize() <= 1) return;

    // Extract values to vector
    std::vector<T> values;
    Node<T>* node = list.getList();  // Get a copy
    while (node) {
        values.push_back(node->value);
        Node<T>* temp = node;
        node = node->next;
        delete temp;  // Clean up copy
    }

    // Apply heap sort
    buildHeap(values);
    for (int i = values.size() - 1; i > 0; --i) {
        std::swap(values[0], values[i]);
        siftDown(values, i, 0);
    }

    // Put sorted values back into original list
    Node<T>* current = list.getList();  // original list head
    int index = 0;
    current = list.getList();  // re-get copy to avoid double-delete
    Node<T>* orig = list.getList();     // walk original list
    while (orig && index < values.size()) {
        orig->value = values[index++];
        orig = orig->next;
    }

    // Clean up the unused copy again
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}
