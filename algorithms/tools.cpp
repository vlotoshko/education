#include "tools.h"
#include <random>

using namespace std;

// Randomizer
template <typename T>
T random(const T &min, const T &max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> uni(min,max);
    auto random_T = uni(rng);
    return random_T;
}


void fillArray(int arr[], int size, int min, int max) {
    for (int i = 0; i < size; ++i)
        arr[i] = random(min, max);
}
