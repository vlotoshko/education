#ifndef TOOLS_H
#define TOOLS_H

#include <chrono>

// Timer
class Timer {
public:
    Timer() : start_(std::chrono::system_clock::now()) {}
    double eplacedTime() {
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        return (double)std::chrono::duration_cast<std::chrono::milliseconds>(end-start_).count()/1000;
    }
private:
    std::chrono::time_point<std::chrono::system_clock> start_;
};

template <typename T>
T random(const T &min, const T &max);

void fillArray(int arr[], int size, int min, int max);

#endif // TOOLS_H
