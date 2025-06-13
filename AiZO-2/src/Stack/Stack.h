#ifndef STACK_H
#define STACK_H

#include <string>

struct StackNode {
    int data;
    StackNode* next = nullptr;
    StackNode* prev = nullptr;
};

class Stack {
private:
    StackNode* head;
    StackNode* tail;
    int size;

    StackNode* findIndex(int index);
    void removeIndex(int index);

public:
    Stack();
    ~Stack();

    void push(int value);
    int pop();
    void removeAll();
    void display() const;

    bool isEmpty() const;
    int IsValueInList(int value);
    int loadFromFile(const std::string& fileName);
    void generateList(int count);
};

#endif // STACK_H
