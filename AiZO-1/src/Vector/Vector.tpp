#include <iostream>
#include <fstream>
#include <type_traits>
#include <algorithm>

// Default constructor
template <typename T>
Vector<T>::Vector() 
    : data(nullptr), 
      capacity(0), 
      size(0) {}

// Constructor with initial capacity
template <typename T>
Vector<T>::Vector(int initialCapacity) 
    : capacity(initialCapacity), 
      size(0) {
    if (initialCapacity > 0) {
        data = new T[initialCapacity];
    } else {
        data = nullptr;
    }
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : capacity(other.capacity),
      size(other.size) {
    if (capacity > 0) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr;
    }
}

// Copy assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) { // Self-assignment check
        delete[] data;
        
        capacity = other.capacity;
        size = other.size;
        
        if (capacity > 0) {
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    return *this;
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

// Helper method to resize array
template <typename T>
void Vector<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    
    // Copy existing elements
    int elementsToCopy = std::min(size, newCapacity);
    for (int i = 0; i < elementsToCopy; ++i) {
        newData[i] = data[i];
    }
    
    // Delete old array and update state
    delete[] data;
    data = newData;
    capacity = newCapacity;
    size = elementsToCopy;
}

// Element access without bounds checking - essential for sorting algorithms
template <typename T>
T& Vector<T>::operator[](int index) {
    return data[index];
}

// Const version
template <typename T>
const T& Vector<T>::operator[](int index) const {
    return data[index];
}

// Check if vector is empty
template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

// Get current size
template <typename T>
int Vector<T>::getSize() const {
    return size;
}

// Get current capacity
template <typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}

// Reserve capacity
template <typename T>
void Vector<T>::reserve(int newCapacity) {
    if (newCapacity > capacity) {
        T* newData = new T[newCapacity];
        
        // Copy existing elements
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        // Delete old array and update state
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

// Clear vector
template <typename T>
void Vector<T>::clear() {
    size = 0;
}

// Add element to end - used by all sorting algorithms to build the vector
template <typename T>
void Vector<T>::pushBack(const T& value) {
    // If we need more space
    if (size >= capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    
    data[size++] = value;
}

// Load vector data from file
template <typename T>
int Vector<T>::loadFromFile(const std::string &filename) {
    clear();

    FILE *file = fopen(filename.c_str(), "r");
    if (file == nullptr) {
        std::cout << "File can not be read." << std::endl;
        return -1;
    }

    int N;
    fscanf(file, "%d", &N);
    
    // Reserve enough space
    reserve(N);

    // Handle different types for file reading
    if (std::is_same<T, int>::value) {
        for (int i = 0; i < N; i++) {
            int value;
            fscanf(file, "%d", &value);
            pushBack(static_cast<T>(value));
        }
    } 
    else if (std::is_same<T, float>::value) {
        for (int i = 0; i < N; i++) {
            float value;
            fscanf(file, "%f", &value);
            pushBack(static_cast<T>(value));
        }
    }
    else if (std::is_same<T, double>::value) {
        for (int i = 0; i < N; i++) {
            double value;
            fscanf(file, "%lf", &value);
            pushBack(static_cast<T>(value));
        }
    }
    else if (std::is_same<T, char>::value) {
        for (int i = 0; i < N; i++) {
            char value;
            fscanf(file, " %c", &value);  // Space before %c consumes whitespace
            pushBack(static_cast<T>(value));
        }
    }
    else {
        std::cout << "Unsupported type for file loading" << std::endl;
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

// Generate vector with random values
template <typename T>
void Vector<T>::generateRandom(int newSize) {
    clear();
    reserve(newSize);
    
    RandomGenerator rng;
    
    for (int i = 0; i < newSize; ++i) {
        // Generate appropriate random value based on type T
        if (std::is_same<T, int>::value) {
            pushBack(static_cast<T>(rng.getInt()));
        }
        else if (std::is_same<T, float>::value) {
            pushBack(static_cast<T>(rng.getFloat()));
        }
        else if (std::is_same<T, double>::value) {
            pushBack(static_cast<T>(rng.getFloat()));
        }
        else if (std::is_same<T, char>::value) {
            pushBack(static_cast<T>(rng.getChar()));
        }
        else {
            // Default case - just insert zeros if type not handled
            pushBack(static_cast<T>(0));
        }
    }
}

// Generate vector with values in ascending order
template <typename T>
void Vector<T>::generateAscending(int newSize) {
    clear();
    reserve(newSize);
    
    // For numeric types
    if (std::is_arithmetic<T>::value) {
        for (int i = 0; i < newSize; i++) {
            pushBack(static_cast<T>(i));
        }
    }
    // For char type
    else if (std::is_same<T, char>::value) {
        char startChar = 'a';
        for (int i = 0; i < newSize; i++) {
            pushBack(static_cast<T>(startChar + i));
        }
    }
    else {
        for (int i = 0; i < newSize; i++) {
            pushBack(static_cast<T>(i));
        }
    }
}

// Generate vector with values in descending order
template <typename T>
void Vector<T>::generateDescending(int newSize) {
    clear();
    reserve(newSize);
    
    // For numeric types
    if (std::is_arithmetic<T>::value) {
        for (int i = newSize - 1; i >= 0; i--) {
            pushBack(static_cast<T>(i));
        }
    }
    // For char type
    else if (std::is_same<T, char>::value) {
        char startChar = 'a' + newSize - 1;
        for (int i = 0; i < newSize; i++) {
            pushBack(static_cast<T>(startChar - i));
        }
    }
    else {
        for (int i = newSize - 1; i >= 0; i--) {
            pushBack(static_cast<T>(i));
        }
    }
}

// Print the vector contents
template <typename T>
void Vector<T>::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}