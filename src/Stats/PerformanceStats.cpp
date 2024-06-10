#include <vector>
#include "PerformanceStats.h"
#include "../Utility/Random.h"

void PerformanceStats::GenerateTestData()
{
    label.clear();
    frameTime.clear();

    for (int i = 0; i < 50; ++i) 
    {
        auto randomStat = random_range(10, 30);

        label.push_back(i);
        frameTime.push_back(randomStat);
    }
}

double PerformanceStats::MaxFrameTime()
{
    double max = *std::ranges::max_element(frameTime);
    return max;
}

double PerformanceStats::MinFrameTime()
{
    double min = *std::ranges::min_element(frameTime);
    return min;
}
