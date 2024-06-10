#include <vector>
#include "PerformanceStats.h"
#include "../Utility/Random.h"

void PerformanceStats::GenerateTestData()
{
    PerformanceStats::label.clear();
    PerformanceStats::frameTime.clear();

    for (int i = 0; i < 50; ++i) 
    {
        PerformanceStats::label.push_back(i);
        PerformanceStats::frameTime.push_back(random_range(0, 1000));
    }
}