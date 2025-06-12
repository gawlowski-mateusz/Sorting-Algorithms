#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
struct ListNode {
    T data;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
};

template <typename T>
class Queue {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;

    ListNode<T>* findIndex(int index);
    void removeIndex(int index);

public:
    Queue();
    ~Queue();

    void push(T value);
    T pop();
    void removeAll();
    bool isEmpty();
};

#include "Queue.tpp"

#endif // QUEUE_H
