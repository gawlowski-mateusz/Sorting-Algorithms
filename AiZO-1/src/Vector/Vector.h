#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include "../RandomGenerator/RandomGenerator.h"

// Vector class template declaration
template <typename T>
class Vector {
private:
    T* data;              // Pointer to dynamic array
    int capacity;         // Total allocated capacity
    int size;             // Current size of the vector

    // Helper method to resize array when needed
    void resize(int newCapacity);

public:
    // Constructor and destructor
    Vector();
    explicit Vector(int initialCapacity);
    Vector(int initialSize, const T& defaultValue);
    Vector(const Vector<T>& other);  // Copy constructor
    Vector<T>& operator=(const Vector<T>& other);  // Copy assignment
    ~Vector();

    // Element access
    T& at(int index);
    const T& at(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data_ptr();

    // Capacity
    bool empty() const;
    int getSize() const;
    int getCapacity() const;
    void reserve(int newCapacity);
    void shrink_to_fit();

    // Modifiers
    void clear();
    void insert(int index, const T& value);
    void erase(int index);
    void pushBack(const T& value);
    void popBack();
    void resize(int newSize, const T& defaultValue = T());

    // File operations
    int loadFromFile(const std::string &filename);
    
    // Generation methods
    void generateRandom(int size);
    void generateAscending(int size);
    void generateDescending(int size);
    
    // Algorithms
    void sort();
    bool search(const T& value) const;
    
    // Utility
    void print() const;
};

#include "Vector.tpp"

#endif // VECTOR_H