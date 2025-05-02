#include <cstdlib>
#include <cmath> 

template <typename T>
int QuickSortDrunk<T>::partition(Vector<T>& array, int left, int right, char pivot_position) {
    T pivot;

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
            pivot = array[std::abs(rng.getInt()) % (right - left + 1) + left];
            break;
        default:
            pivot = array[(left + right) / 2]; // Default to middle
            break;
    }

    int l = left;
    int r = right;

    while (true) {
        while (array[l] < pivot) ++l;
        while (array[r] > pivot) --r;

        if (l >= r) {
            return r;
        }

        if (compareWrong()) {
            ++l;
            --r;
        } else {
            T temp = array[l];
            array[l] = array[r];
            array[r] = temp;
            ++l;
            --r;
        }
    }
}

template <typename T>
bool QuickSortDrunk<T>::compareWrong() {
    int raw = rng.getInt();
    int chance = raw == std::numeric_limits<int>::min()
                 ? 0
                 : std::abs(raw) % 100000;

    return chance < drunk;
}

template <typename T>
void QuickSortDrunk<T>::quickSortDrunk(Vector<T>& array, int left, int right, char pivot_position) {
    if (left >= right) return;

    int m = partition(array, left, right, pivot_position);

    quickSortDrunk(array, left, m, pivot_position);
    quickSortDrunk(array, m + 1, right, pivot_position);
}

template <typename T>
void QuickSortDrunk<T>::sort(List<T>& list, char pivot_position) {
    if (list.getSize() <= 1)
        return;

    Vector<T> values;
    Node<T>* current = list.getList();
    
    while (current) {
        values.pushBack(current->value);
        current = current->next;
    }

    quickSortDrunk(values, 0, values.getSize() - 1, pivot_position);

    list.clear();
    
    for (int i = 0; i < values.getSize(); i++) {
        list.insertAtTail(values[i]);
    }
}
