#pragma once

#include <cstdlib>
#include <ctime>

template<typename T>
inline T random_range(T min, T max) {
    static bool first = true;
    if (first) {
        srand(time(nullptr));
        first = false;
    }

    double scale = rand() / (RAND_MAX + 1.0); // Ensure the upper limit is exclusive
    return static_cast<T>(min + scale * (max - min));
}
