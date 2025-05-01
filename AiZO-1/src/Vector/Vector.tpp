#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

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

// Constructor with initial size and default value
template <typename T>
Vector<T>::Vector(int initialSize, const T& defaultValue)
    : capacity(initialSize),
      size(initialSize) {
    data = new T[initialSize];
    for (int i = 0; i < initialSize; ++i) {
        data[i] = defaultValue;
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

// Element access with bounds checking
template <typename T>
T& Vector<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Const version
template <typename T>
const T& Vector<T>::at(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Element access without bounds checking
template <typename T>
T& Vector<T>::operator[](int index) {
    return data[index];
}

// Const version
template <typename T>
const T& Vector<T>::operator[](int index) const {
    return data[index];
}

// Access first element
template <typename T>
T& Vector<T>::front() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[0];
}

// Const version
template <typename T>
const T& Vector<T>::front() const {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[0];
}

// Access last element
template <typename T>
T& Vector<T>::back() {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
}

// Const version
template <typename T>
const T& Vector<T>::back() const {
    if (size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return data[size - 1];
}

// Get direct access to underlying array
template <typename T>
T* Vector<T>::data_ptr() {
    return data;
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

// Reduce capacity to fit size
template <typename T>
void Vector<T>::shrink_to_fit() {
    if (size < capacity) {
        if (size > 0) {
            T* newData = new T[size];
            
            // Copy existing elements
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            
            // Delete old array and update state
            delete[] data;
            data = newData;
            capacity = size;
        } else {
            delete[] data;
            data = nullptr;
            capacity = 0;
        }
    }
}

// Clear vector
template <typename T>
void Vector<T>::clear() {
    size = 0;
}

// Insert element at specified position
template <typename T>
void Vector<T>::insert(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range for insert");
    }
    
    // If we need more space
    if (size >= capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    
    // Shift elements to make space
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    
    // Insert new element
    data[index] = value;
    size++;
}

// Erase element at specified position
template <typename T>
void Vector<T>::erase(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range for erase");
    }
    
    // Shift elements to remove the gap
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    
    size--;
}

// Add element to end
template <typename T>
void Vector<T>::pushBack(const T& value) {
    // If we need more space
    if (size >= capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    
    data[size++] = value;
}

// Remove last element
template <typename T>
void Vector<T>::popBack() {
    if (size > 0) {
        size--;
    }
}

// Resize vector with optional default value
template <typename T>
void Vector<T>::resize(int newSize, const T& defaultValue) {
    if (newSize > capacity) {
        reserve(newSize);
    }
    
    // Initialize new elements if expanding
    if (newSize > size) {
        for (int i = size; i < newSize; ++i) {
            data[i] = defaultValue;
        }
    }
    
    size = newSize;
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

// Sort the vector
template <typename T>
void Vector<T>::sort() {
    if (size <= 1) return; // Already sorted or empty
    
    // Use standard library sort
    std::sort(data, data + size);
}

// Search for a value in the vector
template <typename T>
bool Vector<T>::search(const T& value) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

// Print the vector contents
template <typename T>
void Vector<T>::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}