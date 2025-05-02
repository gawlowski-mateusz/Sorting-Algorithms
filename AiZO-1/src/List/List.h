#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include "../RandomGenerator/RandomGenerator.h"

// Node class template declaration
template <typename T>
class Node {
public:
    T value;
    Node<T>* next;
    Node<T>* previous;

    // Constructor
    explicit Node(T val) : value(val), next(nullptr), previous(nullptr) {}
};

// List class template declaration
template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    void generateSortedPortion(int size, int start, int end);
    void generateRandomPortion(int size, int start);

public:
    // Constructor and destructor
    List();
    ~List();

    // File operations
    int loadFromFile(const std::string &filename);
    
    // Operations
    void insertAtHead(T value);
    void insertAtTail(T value);
    void deleteNode(T value);
    bool search(T value) const;
    void clear();
    
    // Random generation methods
    void generateList(int size);
    void generateListDescending(int size);
    void generateListAscending(int size);
    void generateListSorted33(int size);
    void generateListSorted66(int size);
    
    // Sorting and manipulation
    void sortList();
    Node<T>* getList();
    
    // Utility
    int getSize() const;
    void printList() const;
    void saveToFile(const std::string& filename) const;
    int checkSortedList() const;
};

#include "List.tpp"

#endif // LIST_H