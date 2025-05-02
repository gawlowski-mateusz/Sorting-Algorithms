#ifndef QUICKSORTDRUNK_H
#define QUICKSORTDRUNK_H

#include "../../List/List.h"
#include "../../Vector/Vector.h"
#include "../../RandomGenerator/RandomGenerator.h"

template <typename T>
class QuickSortDrunk {
public:
    QuickSortDrunk(int drunk = 0) : drunk(drunk) {}  // drunk is 0.1–100 (% chance to flip comparison)
    ~QuickSortDrunk() {}

    void sort(List<T>& list, char pivot_position = 'm');  // 'l', 'm', 'r', 'x'

private:
    int drunk;
    RandomGenerator rng;

    bool compareWrong();

    int partition(Vector<T>& array, int left, int right, char pivot_position);
    void quickSortDrunk(Vector<T>& array, int left, int right, char pivot_position);
};

#endif // QUICKSORTDRUNK_H

#include "QuickSortDrunk.tpp"
