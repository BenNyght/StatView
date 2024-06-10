#pragma once

#include <vector>

class PerformanceStats
{
public:
	static void GenerateTestData();

	static double MaxFrameTime();
	static double MinFrameTime();

	static inline std::vector<double> label = {};
	static inline std::vector<double> frameTime = {};
};