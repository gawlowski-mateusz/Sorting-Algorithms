#include "Queue.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Queue::Queue() : head(nullptr), tail(nullptr), size(0) {}

Queue::~Queue() {
    removeAll();
}

void Queue::push(int value) {
    ListNode* newNode = new ListNode();
    newNode->data = value;
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

int Queue::pop() {
    if (isEmpty()) return -1;
    int value = head->data;
    removeIndex(0);
    return value;
}

void Queue::removeIndex(int index) {
    ListNode* nodeToRemove = findIndex(index);
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

void Queue::removeAll() {
    while (!isEmpty())
        removeIndex(0);
}

ListNode* Queue::findIndex(int index) {
    if (index < 0 || index >= size) return nullptr;

    ListNode* current;
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

bool Queue::isEmpty() const {
    return size == 0;
}

void Queue::display() const {
    ListNode* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

int Queue::IsValueInList(int value) {
    ListNode* current = head;
    int index = 0;
    while (current) {
        if (current->data == value)
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

int Queue::loadFromFile(const std::string& fileName) {
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

void Queue::generateList(int count) {
    removeAll();
    for (int i = 0; i < count; ++i)
        push(rand() % 100);
}
