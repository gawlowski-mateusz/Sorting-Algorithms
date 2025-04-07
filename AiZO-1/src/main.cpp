#include <iostream>
#include <fstream>
#include "./List/List.h"

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

int main() {
    // Create test files for file loading tests
    createTestFiles();
    
    // Test all methods for integer list
    testIntList();
    
    // Test all methods for float list
    testFloatList();
    
    // Test all methods for char list
    testCharList();
    
    std::cout << "\nAll tests completed!" << std::endl;
    
    return 0;
}