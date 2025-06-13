#ifndef QUEUE_H
#define QUEUE_H

#include <string>

struct ListNode {
    int data;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
};

class Queue {
private:
    ListNode* head;
    ListNode* tail;
    int size;

    ListNode* findIndex(int index);
    void removeIndex(int index);

public:
    Queue();
    ~Queue();

    void push(int value);
    int pop();
    void removeAll();
    void display() const;

    bool isEmpty() const;
    int IsValueInList(int value);
    int loadFromFile(const std::string& fileName);
    void generateList(int count);
};

#endif // QUEUE_H
