#pragma once

#include <vector>

class PerformanceStats
{
public:
	static void GenerateTestData();

	static inline std::vector<double> label = {};
	static inline std::vector<double> frameTime = {};
};