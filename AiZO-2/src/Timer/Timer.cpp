#include "Timer.h"
#include <chrono>

Timer::Timer() {
    // Constructor: Initialize any necessary resources
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::reset() {
    // Reset the timer by setting both time points to current time
    startTime = std::chrono::high_resolution_clock::now();
    endTime = startTime;
}

int Timer::start() {
    // Start the timer by capturing the current time
    startTime = std::chrono::high_resolution_clock::now();
    return 0;
}

int Timer::stop() {
    // Stop the timer by capturing the end time
    endTime = std::chrono::high_resolution_clock::now();
    return 0;
}

int Timer::result() {
    // Calculate and return elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTime - startTime
    );
    return static_cast<int>(duration.count());
}