#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <type_traits>

// Constructor
template <typename T>
List<T>::List() 
    : head(nullptr), 
      tail(nullptr), 
      size(0) {}

// Destructor
template <typename T>
List<T>::~List() {
    clear();
}

// Load list data from file
template <typename T>
int List<T>::loadFromFile(const std::string &filename) {
    clear();

    FILE *file = fopen(filename.c_str(), "r");
    if (file == nullptr) {
        std::cout << "File can not be read." << std::endl;
        return -1;
    }

    int N;
    fscanf(file, "%d", &N);

    // Handle different types for file reading
    if (std::is_same<T, int>::value) {
        for (int i = 0; i < N; i++) {
            int value;
            fscanf(file, "%d", &value);
            insertAtTail(static_cast<T>(value));
        }
    } 
    else if (std::is_same<T, float>::value) {
        for (int i = 0; i < N; i++) {
            float value;
            fscanf(file, "%f", &value);
            insertAtTail(static_cast<T>(value));
        }
    }
    else if (std::is_same<T, double>::value) {
        for (int i = 0; i < N; i++) {
            double value;
            fscanf(file, "%lf", &value);
            insertAtTail(static_cast<T>(value));
        }
    }
    else if (std::is_same<T, char>::value) {
        for (int i = 0; i < N; i++) {
            char value;
            fscanf(file, " %c", &value);  // Space before %c consumes whitespace
            insertAtTail(static_cast<T>(value));
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

// Insert at the beginning of the list
template <typename T>
void List<T>::insertAtHead(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
    size++;
}

// Insert at the end of the list
template <typename T>
void List<T>::insertAtTail(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    size++;
}

// Delete a node with specific value
template <typename T>
void List<T>::deleteNode(T value) {
    Node<T>* current = head;

    while (current) {
        if (current->value == value) {
            if (current->previous) {
                current->previous->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->previous = current->previous;
            } else {
                tail = current->previous;
            }

            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

// Search for a value in the list
template <typename T>
bool List<T>::search(T value) const {
    Node<T>* current = head;
    while (current) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Clear the list
template <typename T>
void List<T>::clear() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

// Generate a list with random values
template <typename T>
void List<T>::generateList(int size) {
    clear();
    RandomGenerator rng;
    
    for (int i = 0; i < size; ++i) {
        // Generate appropriate random value based on type T
        if (std::is_same<T, int>::value) {
            insertAtTail(static_cast<T>(rng.getInt()));
        }
        else if (std::is_same<T, float>::value) {
            insertAtTail(static_cast<T>(rng.getFloat()));
        }
        else if (std::is_same<T, double>::value) {
            insertAtTail(static_cast<T>(rng.getDouble()));
        }
        else if (std::is_same<T, char>::value) {
            insertAtTail(static_cast<T>(rng.getChar()));
        }
        else {
            // Default case - just insert zeros if type not handled
            insertAtTail(static_cast<T>(0));
        }
    }
}

template <typename T>
void List<T>::generateSortedPortion(int size, int start, int end) {
    if (std::is_same<T, char>::value) {
        int maxChars = std::min(end - start, 26);  // Only allow up to 'z'
        char startChar = 'a';

        for (int i = 0; i < maxChars; ++i) {
            char currentChar = static_cast<char>(startChar + i);
            insertAtTail(currentChar);
        }

        // If more sorted chars are requested beyond 'z', fill with 'z'
        for (int i = maxChars + start; i < end; ++i) {
            insertAtTail('z');
        }
    } 
    else if (std::is_arithmetic<T>::value) {
        for (int i = start; i < end; i++) {
            insertAtTail(static_cast<T>(i));
        }
    }
}

// Helper function to generate the random portion of the list
template <typename T>
void List<T>::generateRandomPortion(int size, int start) {
    RandomGenerator rng;
    for (int i = start; i < size; i++) {
        // Generate appropriate random value based on type T
        if (std::is_same<T, int>::value) {
            insertAtTail(static_cast<T>(rng.getInt()));
        }
        else if (std::is_same<T, float>::value) {
            insertAtTail(static_cast<T>(rng.getFloat()));
        }
        else if (std::is_same<T, double>::value) {
            insertAtTail(static_cast<T>(rng.getFloat()));
        }
        else if (std::is_same<T, char>::value) {
            insertAtTail(static_cast<T>(rng.getChar()));
        }
        else {
            insertAtTail(static_cast<T>(0));  // Default case for unsupported types
        }
    }
}

// Generate the first 33% of the list in sorted order, the rest in random order
template <typename T>
void List<T>::generateListSorted33(int size) {
    clear();

    int firstPartSize = static_cast<int>(size * 0.33);  // First 33% sorted

    // Generate first 33% in sorted order
    this->generateSortedPortion(size, 0, firstPartSize);

    // Generate the rest (67%) in random order
    this->generateRandomPortion(size, firstPartSize);
}

// Generate the first 66% of the list in sorted order, the rest in random order
template <typename T>
void List<T>::generateListSorted66(int size) {
    clear();

    int firstPartSize = static_cast<int>(size * 0.66);  // First 66% sorted

    // Generate first 66% in sorted order
    this->generateSortedPortion(size, 0, firstPartSize);

    // Generate the rest (34%) in random order
    this->generateRandomPortion(size, firstPartSize);
}

// Sort the list
template <typename T>
void List<T>::sortList() {
    if (size <= 1) return; // Already sorted or empty
    
    // Create a vector of values
    std::vector<T> values;
    Node<T>* current = head;
    
    while (current) {
        values.push_back(current->value);
        current = current->next;
    }
    
    // Sort the vector
    std::sort(values.begin(), values.end());
    
    // Update the list with sorted values
    current = head;
    for (const T& val : values) {
        current->value = val;
        current = current->next;
    }
}

// Get a copy of the list
template <typename T>
Node<T>* List<T>::getList() {
    Node<T>* newHead = nullptr;
    Node<T>* newTail = nullptr;

    // Create a new copy
    Node<T>* current = head;
    while (current) {
        Node<T>* newNode = new Node<T>(current->value);
        
        if (!newHead) {
            newHead = newTail = newNode;
        } else {
            newTail->next = newNode;
            newNode->previous = newTail;
            newTail = newNode;
        }
        
        current = current->next;
    }

    return newHead;
}

// Get the size of the list
template <typename T>
int List<T>::getSize() const {
    return size;
}

// Print the list contents
template <typename T>
void List<T>::printList() const {
    Node<T>* current = head;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Generate a list with values in descending order
template <typename T>
void List<T>::generateListDescending(int size) {
    clear();
    // For numeric types
    if (std::is_arithmetic<T>::value) {
        for (int i = size - 1; i >= 0; i--) {
            insertAtTail(static_cast<T>(i));
        }
    }
    // For char type
    else if (std::is_same<T, char>::value) {
        char startChar = 'a' + size - 1;
        for (int i = 0; i < size; i++) {
            insertAtTail(static_cast<T>(startChar - i));
        }
    }
}

// Generate a list with values in ascending order
template <typename T>
void List<T>::generateListAscending(int size) {
    clear();
    // For numeric types
    if (std::is_arithmetic<T>::value) {
        for (int i = 0; i < size; i++) {
            insertAtTail(static_cast<T>(i));
        }
    }
    // For char type
    else if (std::is_same<T, char>::value) {
        char startChar = 'a';
        for (int i = 0; i < size; i++) {
            insertAtTail(static_cast<T>(startChar + i));
        }
    }
}

// Save list data to a file
template <typename T>
void List<T>::saveToFile(const std::string& filename) const {
    FILE* file = fopen(filename.c_str(), "w");
    if (file == nullptr) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;
        return;
    }

    fprintf(file, "%d\n", size);  // Write the number of elements

    Node<T>* current = head;
    while (current) {
        if (std::is_same<T, int>::value) {
            fprintf(file, "%d\n", static_cast<int>(current->value));
        }
        else if (std::is_same<T, float>::value) {
            fprintf(file, "%f\n", static_cast<float>(current->value));
        }
        else if (std::is_same<T, double>::value) {
            fprintf(file, "%lf\n", static_cast<double>(current->value));
        }
        else if (std::is_same<T, char>::value) {
            fprintf(file, "%c\n", static_cast<char>(current->value));
        }
        else {
            std::cerr << "Unsupported type for saving.\n";
            fclose(file);
            return;
        }

        current = current->next;
    }

    fclose(file);
}