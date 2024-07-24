#pragma once

#include "Captured/Statistic.h"

class StatisticGroup
{
public:
	StatisticGroup(std::string statGroupName) : name(std::move(statGroupName)) {}

	std::string name;
	std::vector<Statistic> statistics;

	void CalculateStatistics();
};