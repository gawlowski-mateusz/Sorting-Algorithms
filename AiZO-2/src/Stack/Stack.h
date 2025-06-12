#ifndef STACK_H
#define STACK_H

template <typename T>
struct StackNode {
    T data;
    StackNode* prev = nullptr;
    StackNode* next = nullptr;
};

template <typename T>
class Stack {
private:
    StackNode<T>* head;
    StackNode<T>* tail;
    int size;

    StackNode<T>* findIndex(int index);
    void removeIndex(int index);

public:
    Stack();
    ~Stack();

    void push(T value);
    T pop();
    void removeAll();
    bool isEmpty();
};

#include "Stack.tpp"

#endif // STACK_H
