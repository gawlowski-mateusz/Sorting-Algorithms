#ifndef VECTOR_H
#define VECTOR_H

#include <string>
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
    Vector(const Vector<T>& other);  // Copy constructor
    Vector<T>& operator=(const Vector<T>& other);  // Copy assignment
    ~Vector();

    // Element access - only what's needed for sorting algorithms
    T& operator[](int index);
    const T& operator[](int index) const;

    // Capacity
    bool empty() const;
    int getSize() const;
    int getCapacity() const;
    void reserve(int newCapacity);

    // Modifiers needed for sorting algorithms
    void clear();
    void pushBack(const T& value);

    // File operations - kept for data loading
    int loadFromFile(const std::string &filename);
    
    // Generation methods - useful for testing sort algorithms
    void generateRandom(int size);
    void generateAscending(int size);
    void generateDescending(int size);

    // Utility
    void print() const;
};

#include "Vector.tpp"

#endif // VECTOR_H