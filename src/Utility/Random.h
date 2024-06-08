#pragma once

#include <cstdlib>

template <typename T>
inline T random_range(T min, T max)
{
    T scale = rand() / static_cast<T>(RAND_MAX);
    return min + scale * ( max - min );
}
