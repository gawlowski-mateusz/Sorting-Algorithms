#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void reset();
    int start();
    int stop();
    int result();

private:
    // Everything else you need, both fields and methods.
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
};