#include <vector>
#include <numeric>
#include "PerformanceStats.h"
#include "../Utility/Random.h"

void PerformanceStats::GenerateTestData()
{
    label.clear();
    frameTime.clear();

    for (int i = 0; i < 50; ++i) 
    {
	    const auto randomStat = random_range(10, 30);

        label.push_back(i);
        frameTime.push_back(randomStat);
    }
}

double PerformanceStats::FrameTimeAverage()
{
	const double total = std::accumulate(frameTime.begin(), frameTime.end(), 0.0);
    const double count = static_cast<double>(frameTime.size());
    const double average = total / count;
	return average;
}

double PerformanceStats::FrameTimeMax()
{
	const double max = *std::ranges::max_element(frameTime);
    return max;
}

double PerformanceStats::FrameTimeMin()
{
	const double min = *std::ranges::min_element(frameTime);
    return min;
}
