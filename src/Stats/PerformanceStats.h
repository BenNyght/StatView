#pragma once

#include <vector>

class PerformanceStats
{
public:
	static void GenerateTestData();

	static double FrameTimeAverage();
	static double FrameTimeMax();
	static double FrameTimeMin();

	static inline std::vector<double> label = {};
	static inline std::vector<double> frameTime = {};
};