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