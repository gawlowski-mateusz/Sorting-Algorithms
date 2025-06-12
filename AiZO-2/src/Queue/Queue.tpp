#include <stdexcept>

template <typename T>
Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
Queue<T>::~Queue() {
    while (head != nullptr)
        pop();
}

template <typename T>
void Queue<T>::push(T value) {
    ListNode<T>* newNode = new ListNode<T>();
    newNode->data = value;
    if (size == 0) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    T value = head->data;
    removeIndex(0);
    return value;
}

template <typename T>
void Queue<T>::removeIndex(int index) {
    if (index < 0 || index >= size) return;

    if (index == 0) {
        ListNode<T>* nodeToRemove = findIndex(index);
        head = nodeToRemove->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete nodeToRemove;
        size--;
        return;
    }

    ListNode<T>* currNode = findIndex(index);
    ListNode<T>* prevNode = currNode->prev;

    prevNode->next = currNode->next;
    if (currNode == tail) {
        tail = prevNode;
    } else {
        currNode->next->prev = prevNode;
    }

    delete currNode;
    size--;
}

template <typename T>
void Queue<T>::removeAll() {
    while (head != nullptr)
        removeIndex(0);
}

template <typename T>
ListNode<T>* Queue<T>::findIndex(int index) {
    if (index < 0 || index >= size) return nullptr;

    ListNode<T>* currentNode;
    if (index > size / 2) {
        currentNode = tail;
        for (int i = size - 1; i > index; --i) {
            currentNode = currentNode->prev;
        }
    } else {
        currentNode = head;
        for (int i = 0; i < index; ++i) {
            currentNode = currentNode->next;
        }
    }
    return currentNode;
}

template <typename T>
bool Queue<T>::isEmpty() {
    return size == 0;
}
