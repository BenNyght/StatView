#include "Statistic.h"
#include "StatisticUtility.h"

void Statistic::CalculateStatistic()
{
	min = StatisticUtility::GetMin(values);
    max = StatisticUtility::GetMax(values);
    average = StatisticUtility::GetAverage(values);
    median = StatisticUtility::GetMedian(values);
    standardDeviation = StatisticUtility::GetStandardDeviation(values, average);
    p95 = StatisticUtility::GetPercentile(values, 0.95);
    p995 = StatisticUtility::GetPercentile(values, 0.995);
}

void Statistic::AddValue(double value, double label)
{
    size++;
    values.push_back(value);
    labels.push_back(label);
    CalculateStatistic();
}

void Statistic::AddValue(double value)
{
    AddValue(value, size);
}

size_t Statistic::GetIndexCount()
{
    return 8;
}

std::string Statistic::GetIndexName(const size_t index)
{
	switch (index)
	{
		case 0:
            return "Minimum";
        case 1:
            return "Maximum";
        case 2:
            return "Average";
        case 3:
            return "Median";
        case 4:
            return "Standard Deviation";
        case 5:
            return "95th Percentile";
        case 6:
            return "99.5th Percentile";
        case 7:
            return "Count";
		default:
		    return "Unknown";
	}
}

const double Statistic::GetIndexValue(const size_t index) const
{
	switch (index)
	{
		case 0:
            return min;
        case 1:
            return max;
        case 2:
            return average;
        case 3:
            return median;
        case 4:
            return standardDeviation;
        case 5:
            return p95;
        case 6:
            return p995;
        case 7:
            return static_cast<double>(size);
		default:
		    return 0;
	}
}
