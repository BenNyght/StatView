
#include "StatisticGroup.h"

void StatisticGroup::CalculateStatistics()
{
	for (auto& statistic : statistics)
	{
		statistic.CalculateStatistic();
	}
}