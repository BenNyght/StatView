
#pragma once

#include <vector>

class StatisticUtility
{
public:
    static double GetMedian(const std::vector<double>& samples);
    static double GetPercentile(const std::vector<double>& samples, double percentile);
    static double GetStandardDeviation(const std::vector<double>& samples, double average);
    static double GetMin(const std::vector<double>& samples);
    static double GetMax(const std::vector<double>& samples);
    static double GetAverage(const std::vector<double>& samples);
    static double GetSum(const std::vector<double>& samples);

private:
    static std::vector<double> SortableSamples;
};
