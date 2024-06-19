#pragma once

#include <string>
#include <vector>

class Statistic 
{
public:
    Statistic() = default;
    Statistic(std::string statName) : name(std::move(statName)) {}
    Statistic(std::string statName, std::string statSuffix) : name(std::move(statName)), suffix(std::move(statSuffix)) {}

	std::string name;
    std::string suffix;

    double min;
    double max;
    double average;
    double median;
    double standardDeviation;
    double p95;
    double p995;

    size_t size;
    std::vector<double> values;
    std::vector<double> labels;

public:
    void CalculateStatistic();
    void AddValue(double value);
    void AddValue(double value, double label);
};
