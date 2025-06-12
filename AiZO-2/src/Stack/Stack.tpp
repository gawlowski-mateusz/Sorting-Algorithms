#include <stdexcept>

template <typename T>
Stack<T>::Stack() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
Stack<T>::~Stack() {
    while (head != nullptr)
        pop();
}

template <typename T>
void Stack<T>::push(T value) {
    StackNode<T>* newNode = new StackNode<T>();
    newNode->data = value;
    if (size == 0) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    T value = head->data;
    removeIndex(0);
    return value;
}

template <typename T>
void Stack<T>::removeIndex(int index) {
    if (index < 0 || index >= size) return;

    if (index == 0) {
        StackNode<T>* nodeToRemove = findIndex(index);
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

    StackNode<T>* currNode = findIndex(index);
    StackNode<T>* prevNode = currNode->prev;

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
void Stack<T>::removeAll() {
    while (head != nullptr)
        removeIndex(0);
}

template <typename T>
StackNode<T>* Stack<T>::findIndex(int index) {
    if (index < 0 || index >= size) return nullptr;

    StackNode<T>* currentNode;
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
bool Stack<T>::isEmpty() {
    return size == 0;
}
