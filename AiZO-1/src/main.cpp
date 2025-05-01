#include <iostream>
#include <fstream>
#include "./List/List.h"
#include "./Vector/Vector.h"

#include "./SortingAlgorithms/QuickSort/QuickSort.h"
#include "./SortingAlgorithms/InsertionSort/InsertionSort.h"
#include "./SortingAlgorithms/ShellSort/ShellSort.h"
#include "./SortingAlgorithms/HeapSort/HeapSort.h"

template<typename T>
void printArray(const T* array, int size) {
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

void testSortingAlgorithms() {
    std::cout << "\n===== TESTING SORTING ALGORITHMS =====\n" << std::endl;

    List<int> intList1;
    List<int> intList2;
    List<int> intList3;
    List<int> intList4;


    // Test generateList
    std::cout << "\nTesting generateList:" << std::endl;
    intList1.generateList(10);
    intList2.generateList(10);
    intList3.generateList(10);
    intList4.generateList(10);


    // QuickSort
    std::cout << "\n\n\nOriginal array:\n";
    intList1.printList();

    QuickSort<int> quickSort;
    std::cout << "\nQuickSort (pivot = 'x'):\n";
    quickSort.sort(intList1, 'x');

    std::cout << "\nSorted array:\n";
    intList1.printList();


    // InsertionSort
    std::cout << "\n\n\nOriginal array:\n";
    intList2.printList();

    InsertionSort<int> insertionSort;
    std::cout << "\nInsertionSort:\n";
    insertionSort.sort(intList2);

    std::cout << "\nSorted array:\n";
    intList2.printList();


    // ShellSort
    std::cout << "\n\n\nOriginal array:\n";
    intList3.printList();

    ShellSort<int> shellSort;
    std::cout << "\nShellSort (Tokuda sequence):\n";
    shellSort.sort(intList3, 2); // 1 for Papiernow, 2 for Tokuda

    std::cout << "\nSorted array:\n";
    intList3.printList();


    // HeapSort
    std::cout << "\n\n\nOriginal array:\n";
    intList4.printList();

    HeapSort<int> heapSort;
    std::cout << "\nHeapSort:\n";
    heapSort.sort(intList4);

    std::cout << "\nSorted array:\n";
    intList4.printList();    
}

// Helper function to write test data to a file
template <typename T>
void writeTestFile(const std::string& filename, const std::vector<T>& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << data.size() << std::endl;
        for (const auto& item : data) {
            file << item << std::endl;
        }
        file.close();
        std::cout << "Test file " << filename << " created successfully." << std::endl;
    } else {
        std::cout << "Failed to create test file " << filename << std::endl;
    }
}

// Helper function to create test files
void createTestFiles() {
    // Integer test file
    std::vector<int> intData = {5, 10, 15, 20, 25};
    writeTestFile("./Data/int_test.txt", intData);
    
    // Float test file
    std::vector<float> floatData = {5.5f, 10.1f, 15.7f, 20.3f, 25.9f};
    writeTestFile("./Data/float_test.txt", floatData);
    
    // Character test file
    std::vector<char> charData = {'a', 'b', 'c', 'd', 'e'};
    writeTestFile("./Data/char_test.txt", charData);
}

// Function to test all methods of a List<int>
void testIntList() {
    std::cout << "\n===== TESTING INTEGER LIST =====\n" << std::endl;
    
    List<int> intList;
    
    // Test insertAtHead and insertAtTail
    std::cout << "Testing insertAtHead and insertAtTail:" << std::endl;
    intList.insertAtHead(10);
    intList.insertAtHead(5);
    intList.insertAtTail(15);
    intList.insertAtTail(20);
    std::cout << "List after insertions: ";
    intList.printList();
    std::cout << "List size: " << intList.getSize() << std::endl;
    
    // Test search
    std::cout << "\nTesting search:" << std::endl;
    std::cout << "Is 10 in the list? " << (intList.search(10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 30 in the list? " << (intList.search(30) ? "Yes" : "No") << std::endl;
    
    // Test deleteNode
    std::cout << "\nTesting deleteNode:" << std::endl;
    std::cout << "Deleting 10 from the list..." << std::endl;
    intList.deleteNode(10);
    std::cout << "List after deletion: ";
    intList.printList();
    std::cout << "List size: " << intList.getSize() << std::endl;
    
    // Test sortList
    std::cout << "\nTesting sortList:" << std::endl;
    intList.sortList();
    std::cout << "List after sorting: ";
    intList.printList();
    
    // Test getList (copy)
    std::cout << "\nTesting getList (copy):" << std::endl;
    Node<int>* copy = intList.getList();
    std::cout << "Copy of the list: ";
    // Print the copy manually
    Node<int>* current = copy;
    while (current) {
        std::cout << current->value << " ";
        Node<int>* temp = current;
        current = current->next;
        delete temp; // Clean up the copied nodes
    }
    std::cout << std::endl;
    
    // Test generateList
    std::cout << "\nTesting generateList:" << std::endl;
    intList.generateList(8);
    std::cout << "Randomly generated list: ";
    intList.printList();
    
    // Test generateListAscending
    std::cout << "\nTesting generateListAscending:" << std::endl;
    intList.generateListAscending(5);
    std::cout << "Ascending list: ";
    intList.printList();
    
    // Test generateListDescending
    std::cout << "\nTesting generateListDescending:" << std::endl;
    intList.generateListDescending(5);
    std::cout << "Descending list: ";
    intList.printList();
    
    // Test loadFromFile
    std::cout << "\nTesting loadFromFile:" << std::endl;
    int result = intList.loadFromFile("./Data/int_test.txt");
    if (result == 0) {
        std::cout << "List loaded from file: ";
        intList.printList();
    } else {
        std::cout << "Failed to load list from file." << std::endl;
    }
    
    // Test clear
    std::cout << "\nTesting clear:" << std::endl;
    intList.clear();
    std::cout << "List after clearing: ";
    intList.printList();
    std::cout << "List size: " << intList.getSize() << std::endl;
}

// Function to test all methods of a List<float>
void testFloatList() {
    std::cout << "\n===== TESTING FLOAT LIST =====\n" << std::endl;
    
    List<float> floatList;
    
    // Test insertAtHead and insertAtTail
    std::cout << "Testing insertAtHead and insertAtTail:" << std::endl;
    floatList.insertAtHead(10.5f);
    floatList.insertAtHead(5.2f);
    floatList.insertAtTail(15.7f);
    floatList.insertAtTail(20.1f);
    std::cout << "List after insertions: ";
    floatList.printList();
    std::cout << "List size: " << floatList.getSize() << std::endl;
    
    // Test search
    std::cout << "\nTesting search:" << std::endl;
    std::cout << "Is 10.5 in the list? " << (floatList.search(10.5f) ? "Yes" : "No") << std::endl;
    std::cout << "Is 30.0 in the list? " << (floatList.search(30.0f) ? "Yes" : "No") << std::endl;
    
    // Test deleteNode
    std::cout << "\nTesting deleteNode:" << std::endl;
    std::cout << "Deleting 10.5 from the list..." << std::endl;
    floatList.deleteNode(10.5f);
    std::cout << "List after deletion: ";
    floatList.printList();
    std::cout << "List size: " << floatList.getSize() << std::endl;
    
    // Test sortList
    std::cout << "\nTesting sortList:" << std::endl;
    floatList.sortList();
    std::cout << "List after sorting: ";
    floatList.printList();
    
    // Test generateList
    std::cout << "\nTesting generateList:" << std::endl;
    floatList.generateList(8);
    std::cout << "Randomly generated list: ";
    floatList.printList();
    
    // Test generateListAscending
    std::cout << "\nTesting generateListAscending:" << std::endl;
    floatList.generateListAscending(5);
    std::cout << "Ascending list: ";
    floatList.printList();
    
    // Test generateListDescending
    std::cout << "\nTesting generateListDescending:" << std::endl;
    floatList.generateListDescending(5);
    std::cout << "Descending list: ";
    floatList.printList();
    
    // Test loadFromFile
    std::cout << "\nTesting loadFromFile:" << std::endl;
    int result = floatList.loadFromFile("./Data/float_test.txt");
    if (result == 0) {
        std::cout << "List loaded from file: ";
        floatList.printList();
    } else {
        std::cout << "Failed to load list from file." << std::endl;
    }
    
    // Test clear
    std::cout << "\nTesting clear:" << std::endl;
    floatList.clear();
    std::cout << "List after clearing: ";
    floatList.printList();
    std::cout << "List size: " << floatList.getSize() << std::endl;
}

// Function to test all methods of a List<char>
void testCharList() {
    std::cout << "\n===== TESTING CHAR LIST =====\n" << std::endl;
    
    List<char> charList;
    
    // Test insertAtHead and insertAtTail
    std::cout << "Testing insertAtHead and insertAtTail:" << std::endl;
    charList.insertAtHead('b');
    charList.insertAtHead('a');
    charList.insertAtTail('c');
    charList.insertAtTail('d');
    std::cout << "List after insertions: ";
    charList.printList();
    std::cout << "List size: " << charList.getSize() << std::endl;
    
    // Test search
    std::cout << "\nTesting search:" << std::endl;
    std::cout << "Is 'b' in the list? " << (charList.search('b') ? "Yes" : "No") << std::endl;
    std::cout << "Is 'z' in the list? " << (charList.search('z') ? "Yes" : "No") << std::endl;
    
    // Test deleteNode
    std::cout << "\nTesting deleteNode:" << std::endl;
    std::cout << "Deleting 'b' from the list..." << std::endl;
    charList.deleteNode('b');
    std::cout << "List after deletion: ";
    charList.printList();
    std::cout << "List size: " << charList.getSize() << std::endl;
    
    // Test sortList
    std::cout << "\nTesting sortList:" << std::endl;
    charList.sortList();
    std::cout << "List after sorting: ";
    charList.printList();
    
    // Test generateList
    std::cout << "\nTesting generateList:" << std::endl;
    charList.generateList(8);
    std::cout << "Randomly generated list: ";
    charList.printList();
    
    // Test generateListAscending
    std::cout << "\nTesting generateListAscending:" << std::endl;
    charList.generateListAscending(5);
    std::cout << "Ascending list: ";
    charList.printList();
    
    // Test generateListDescending
    std::cout << "\nTesting generateListDescending:" << std::endl;
    charList.generateListDescending(5);
    std::cout << "Descending list: ";
    charList.printList();
    
    // Test loadFromFile
    std::cout << "\nTesting loadFromFile:" << std::endl;
    int result = charList.loadFromFile("./Data/char_test.txt");
    if (result == 0) {
        std::cout << "List loaded from file: ";
        charList.printList();
    } else {
        std::cout << "Failed to load list from file." << std::endl;
    }
    
    // Test clear
    std::cout << "\nTesting clear:" << std::endl;
    charList.clear();
    std::cout << "List after clearing: ";
    charList.printList();
    std::cout << "List size: " << charList.getSize() << std::endl;
}

void testVector() {
    // Create a vector of integers
    Vector<int> intVector;
    
    // Test push_back
    std::cout << "Adding elements with pushBack():\n";
    intVector.pushBack(10);
    intVector.pushBack(20);
    intVector.pushBack(30);
    intVector.pushBack(40);
    intVector.pushBack(50);
    intVector.print();
    
    // Test random generation
    std::cout << "\nGenerating random vector:\n";
    Vector<int> randomVector;
    randomVector.generateRandom(10);
    randomVector.print();
    
    // Test ascending generation
    std::cout << "\nGenerating ascending vector:\n";
    Vector<int> ascendingVector;
    ascendingVector.generateAscending(10);
    ascendingVector.print();
    
    // Test descending generation
    std::cout << "\nGenerating descending vector:\n";
    Vector<int> descendingVector;
    descendingVector.generateDescending(10);
    descendingVector.print();
    
    // Test sorting
    std::cout << "\nSorting random vector:\n";
    randomVector.sort();
    randomVector.print();
    
    // Test element access
    std::cout << "\nTesting element access:\n";
    std::cout << "intVector[2] = " << intVector[2] << std::endl;
    std::cout << "intVector.at(3) = " << intVector.at(3) << std::endl;
    std::cout << "intVector.front() = " << intVector.front() << std::endl;
    std::cout << "intVector.back() = " << intVector.back() << std::endl;
    
    // Test insert and erase
    std::cout << "\nInserting 25 at position 2:\n";
    intVector.insert(2, 25);
    intVector.print();
    
    std::cout << "Erasing element at position 1:\n";
    intVector.erase(1);
    intVector.print();
    
    // Test capacity functions
    std::cout << "\nCapacity functions:\n";
    std::cout << "Size: " << intVector.getSize() << std::endl;
    std::cout << "Capacity: " << intVector.getCapacity() << std::endl;
    
    // Test reserve and shrink_to_fit
    std::cout << "\nReserving space for 20 elements:\n";
    intVector.reserve(20);
    std::cout << "New capacity: " << intVector.getCapacity() << std::endl;
    
    std::cout << "Shrinking to fit:\n";
    intVector.shrink_to_fit();
    std::cout << "New capacity: " << intVector.getCapacity() << std::endl;
    
    // Test search
    std::cout << "\nSearching for values:\n";
    std::cout << "Contains 25? " << (intVector.search(25) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 15? " << (intVector.search(15) ? "Yes" : "No") << std::endl;
    
    // Test clear
    std::cout << "\nClearing vector:\n";
    intVector.clear();
    std::cout << "Size after clear: " << intVector.getSize() << std::endl;
    
    // Test char vector
    std::cout << "\nTest with character type:\n";
    Vector<char> charVector;
    charVector.generateAscending(10);
    charVector.print();
}

int main() {
    // Create test files for file loading tests
    createTestFiles();
    
    // Test all methods for integer list
    testIntList();
    
    // Test all methods for float list
    testFloatList();
    
    // Test all methods for char list
    testCharList();

    // Test all sorting algorithms
    testSortingAlgorithms();

    testVector();

    std::cout << "\nAll tests completed!" << std::endl;
    
    return 0;
}