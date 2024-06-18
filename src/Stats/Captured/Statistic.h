#include <string>
#include <vector>

struct Statistic 
{
public:
    Statistic(std::string name, std::string type);

	std::string name;
    std::string type;

    double min;
    double max;
    double average;
    double median;
    double standardDeviation;
    double p95;
    double p995;

    std::vector<double> values;

public:
    void CalculateStatistic();
    void AddValue(double value);
};
