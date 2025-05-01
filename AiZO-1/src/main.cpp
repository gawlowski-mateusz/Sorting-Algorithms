#include <iostream>
#include <fstream>
#include <string>
#include "./List/List.h"

#include "./SortingAlgorithms/QuickSort/QuickSort.h"
#include "./SortingAlgorithms/InsertionSort/InsertionSort.h"
#include "./SortingAlgorithms/ShellSort/ShellSort.h"
#include "./SortingAlgorithms/HeapSort/HeapSort.h"

std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) result += std::tolower(c);
    return result;
}

template<typename T>
void sortAndSave(List<T>& list, const std::string& algorithm, const std::string& outputFile) {
    if (algorithm == "quick") {
        QuickSort<T> sorter;
        sorter.sort(list, 'x');
    } else if (algorithm == "insertion") {
        InsertionSort<T> sorter;
        sorter.sort(list);
    } else if (algorithm == "shell") {
        ShellSort<T> sorter;
        sorter.sort(list, 2);
    } else if (algorithm == "heap") {
        HeapSort<T> sorter;
        sorter.sort(list);
    } else {
        std::cerr << "Unknown sorting algorithm.\n";
        return;
    }

    std::cout << "\nSorted list:\n";
    list.printList();

    if (!outputFile.empty()) {
        list.saveToFile(outputFile);
        std::cout << "Saved sorted data to: " << outputFile << '\n';
    }
}

template<typename T>
void handleFileMode(const std::string& algorithm, const std::string& inputFile, const std::string& outputFile) {
    List<T> list;
    if (list.loadFromFile(inputFile) != 0) {
        std::cerr << "Failed to load data from file.\n";
        return;
    }

    std::cout << "\nLoaded list:\n";
    list.printList();

    sortAndSave(list, algorithm, outputFile);
}

template<typename T>
void handleTestMode(const std::string& algorithm, int size, const std::string& sortType, const std::string& outputFile) {
    List<T> list;

    if (sortType == "random") list.generateList(size);
    else if (sortType == "ascending") list.generateListAscending(size);
    else if (sortType == "descending") list.generateListDescending(size);
    else {
        std::cerr << "Unknown sort type: use random, ascending or descending.\n";
        return;
    }

    std::cout << "\nGenerated list (" << sortType << "):\n";
    list.printList();

    sortAndSave(list, algorithm, outputFile);
}

void printHelp() {
    std::cout << "\nUsage:\n"
              << "./main --file <algorithm> <type> <inputFile> [outputFile]\n"
              << "./main --test <algorithm> <type> <size> <sort> <outputFile>\n"
              << "./main --help\n\n"
              << "Arguments:\n"
              << "  <algorithm>   quick | insertion | shell | heap\n"
              << "  <type>        int | float | double | char\n"
              << "  <sort>        random | ascending | descending\n\n"
              << "Examples:\n"
              << "  ./main --file quick int ./input.txt ./sorted.txt\n"
              << "  ./main --test heap double 100 random ./output.txt\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use --help for usage.\n";
        return 1;
    }

    std::string run_type = toLower(argv[1]);

    if (run_type == "--help") {
        printHelp();
        return 0;
    }

    if (run_type == "--file") {
        if (argc < 5) {
            std::cerr << "Usage: ./main --file <algorithm> <type> <inputFile> [outputFile]\n";
            return 1;
        }

        std::string algorithm = toLower(argv[2]);
        std::string type = toLower(argv[3]);
        std::string inputFile = argv[4];
        std::string outputFile = (argc >= 6) ? argv[5] : "";

        if (type == "int") handleFileMode<int>(algorithm, inputFile, outputFile);
        else if (type == "float") handleFileMode<float>(algorithm, inputFile, outputFile);
        else if (type == "double") handleFileMode<double>(algorithm, inputFile, outputFile);
        else if (type == "char") handleFileMode<char>(algorithm, inputFile, outputFile);
        else {
            std::cerr << "Unsupported data type.\n";
            return 1;
        }

    } else if (run_type == "--test") {
        if (argc < 7) {
            std::cerr << "Usage: ./main --test <algorithm> <type> <size> <sort> <outputFile>\n";
            return 1;
        }

        std::string algorithm = toLower(argv[2]);
        std::string type = toLower(argv[3]);
        int size = std::stoi(argv[4]);
        std::string sortType = toLower(argv[5]);
        std::string outputFile = argv[6];

        if (type == "int") handleTestMode<int>(algorithm, size, sortType, outputFile);
        else if (type == "float") handleTestMode<float>(algorithm, size, sortType, outputFile);
        else if (type == "double") handleTestMode<double>(algorithm, size, sortType, outputFile);
        else if (type == "char") handleTestMode<char>(algorithm, size, sortType, outputFile);
        else {
            std::cerr << "Unsupported data type.\n";
            return 1;
        }

    } else {
        std::cerr << "Unknown run type. Use --help for usage.\n";
        return 1;
    }

    return 0;
}
