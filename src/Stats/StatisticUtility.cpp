
#include "StatisticUtility.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <limits>

std::vector<double> StatisticUtility::SortableSamples;

double StatisticUtility::GetMedian(const std::vector<double>& samples)
{
    if (samples.empty())
    {
        return 0.0;
    }

    SortableSamples.clear();
    SortableSamples = samples;
    std::sort(SortableSamples.begin(), SortableSamples.end());

    size_t size = SortableSamples.size();
    size_t mid = size / 2;
    double median = (size % 2 != 0) ? SortableSamples[mid] : (SortableSamples[mid] + SortableSamples[mid - 1]) / 2.0;

    return median;
}

double StatisticUtility::GetPercentile(const std::vector<double>& samples, double percentile)
{
    const double floatingTolerance = 0.01;

    if (samples.empty())
    {
        return 0.0;
    }

    SortableSamples.clear();
    SortableSamples = samples;
    std::sort(SortableSamples.begin(), SortableSamples.end());

    size_t sampleCount = SortableSamples.size();
    double n = (sampleCount - 1) * percentile + 1.0;

    if (std::abs(n - 1.0) < floatingTolerance)
    {
        return SortableSamples[0];
    }

    if (std::abs(n - sampleCount) < floatingTolerance)
    {
        return SortableSamples[sampleCount - 1];
    }

    int k = static_cast<int>(n);
    double d = n - k;

    return SortableSamples[k - 1] + d * (SortableSamples[k] - SortableSamples[k - 1]);
}

double StatisticUtility::GetStandardDeviation(const std::vector<double>& samples, double average)
{
    size_t samplesCount = samples.size();

    if (samplesCount == 0)
    {
        return 0.0;
    }

    double sumOfSquaresOfDifferences = 0.0;

    for (const auto& sample : samples)
    {
        sumOfSquaresOfDifferences += (sample - average) * (sample - average);
    }

    return std::sqrt(sumOfSquaresOfDifferences / samplesCount);
}

double StatisticUtility::GetMin(const std::vector<double>& samples)
{
    if (samples.empty())
    {
        return 0.0;
    }

    return *std::ranges::min_element(samples.begin(), samples.end());
}

double StatisticUtility::GetMax(const std::vector<double>& samples)
{
    if (samples.empty())
    {
        return 0.0;
    }

    return *std::ranges::max_element(samples);
}

double StatisticUtility::GetAverage(const std::vector<double>& samples)
{
    size_t samplesCount = samples.size();

    if (samplesCount == 0)
    {
        return 0.0;
    }

    return GetSum(samples) / samplesCount;
}

double StatisticUtility::GetSum(const std::vector<double>& samples)
{
    if (samples.empty())
    {
        return 0.0;
    }

    return std::accumulate(samples.begin(), samples.end(), 0.0);
}
