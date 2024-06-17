#include "Statistic.h"
#include "StatisticUtility.h"

Statistic::Statistic(std::string name, std::string type) 
    : name(name), type(type)
{

}

void Statistic::CalculateStatistic()
{
	min = StatisticUtility::GetMin(values);
    max = StatisticUtility::GetMax(values);
    average = StatisticUtility::GetAverage(values);
    median = StatisticUtility::GetMedianValue(values);
    standardDeviation = StatisticUtility::GetStandardDeviation(values, average);
    p95 = StatisticUtility::GetPercentile(values, 0.95);
    p995 = StatisticUtility::GetPercentile(values, 0.995);
}

void Statistic::AddValue(double value)
{
    values.push_back(value);
    CalculateStatistic();
}
