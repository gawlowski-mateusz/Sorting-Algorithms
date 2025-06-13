#include "Stack.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Stack::Stack() : head(nullptr), tail(nullptr), size(0) {}

Stack::~Stack() {
    while (!isEmpty())
        pop();
}

void Stack::push(int value) {
    StackNode* newNode = new StackNode();
    newNode->data = value;
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

int Stack::pop() {
    if (isEmpty()) return -1;
    int value = head->data;
    removeIndex(0);
    return value;
}

void Stack::removeIndex(int index) {
    StackNode* nodeToRemove = findIndex(index);
    if (!nodeToRemove) return;

    if (nodeToRemove == head) {
        head = nodeToRemove->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
    } else if (nodeToRemove == tail) {
        tail = nodeToRemove->prev;
        if (tail) tail->next = nullptr;
    } else {
        nodeToRemove->prev->next = nodeToRemove->next;
        nodeToRemove->next->prev = nodeToRemove->prev;
    }

    delete nodeToRemove;
    size--;
}

void Stack::removeAll() {
    while (!isEmpty())
        removeIndex(0);
}

StackNode* Stack::findIndex(int index) {
    if (index < 0 || index >= size) return nullptr;
    StackNode* current = nullptr;

    if (index > size / 2) {
        current = tail;
        for (int i = size - 1; i > index; --i)
            current = current->prev;
    } else {
        current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
    }
    return current;
}

bool Stack::isEmpty() const {
    return size == 0;
}

void Stack::display() const {
    StackNode* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

int Stack::IsValueInList(int value) {
    StackNode* current = head;
    int index = 0;
    while (current) {
        if (current->data == value)
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

int Stack::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Unable to open file: " << fileName << "\n";
        return -1;
    }

    int count, value;
    file >> count;
    while (count-- && file >> value)
        push(value);

    file.close();
    return 0;
}

void Stack::generateList(int count) {
    removeAll();
    for (int i = 0; i < count; ++i)
        push(rand() % 100);
}
