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

    double min = 0;
    double max = 0;
    double average = 0;
    double median = 0;
    double standardDeviation = 0;
    double p95 = 0;
    double p995 = 0;

    size_t size = 0;
    std::vector<double> values {};
    std::vector<double> labels {};

    void CalculateStatistic();
    void AddValue(double value);
    void AddValue(double value, double label);

    static size_t GetIndexCount();
    static std::string GetIndexName(size_t index);
    [[nodiscard]] const double GetIndexValue(size_t index) const;
};
