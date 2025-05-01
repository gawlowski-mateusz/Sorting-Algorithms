#include "RandomGenerator.h"
#include <limits>

// Constructor
RandomGenerator::RandomGenerator() : gen(rd()) {
}

// Generate a random integer in the full range of int
int RandomGenerator::getInt() {
    std::uniform_int_distribution<int> distrib(
        std::numeric_limits<int>::min(),
        std::numeric_limits<int>::max()
    );
    return distrib(gen);
}

// Generate a random char in the range a-z
char RandomGenerator::getChar() {
    std::uniform_int_distribution<int> distrib('a', 'z');
    return static_cast<char>(distrib(gen));
}

// Generate a random float in the full float range
float RandomGenerator::getFloat() {
    std::uniform_real_distribution<float> distrib(-1e38, 1e38);

    return distrib(gen);
}

// Generate a random double in the full double range
double RandomGenerator::getDouble() {
    std::uniform_real_distribution<double> distrib(-1e156, 1e156);
    return distrib(gen);
}

// Get access to the underlying generator
std::mt19937& RandomGenerator::getGenerator() {
    return gen;
}