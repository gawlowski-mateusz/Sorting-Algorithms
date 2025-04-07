#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>
#include <cstdint>

class RandomGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;

public:
    RandomGenerator();
    
    // Generate a random integer in the full range of int
    int getInt();
    
    // Generate a random char in the full range (0-255)
    char getChar();
    
    // Generate a random float in the full float range
    float getFloat();
    
    // Generate a random double in the full double range
    double getDouble();
    
    // Get access to the underlying generator
    std::mt19937& getGenerator();
};

#endif // RANDOM_GENERATOR_H