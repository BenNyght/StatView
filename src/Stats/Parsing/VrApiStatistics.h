#pragma once

#include "Captured/Statistic.h"

class VrApiStatistics
{
public:
	Statistic Fps { "FPS" };
	Statistic FpsWithASW { "FPS w/Generated Frames" };
	Statistic PredictionTime { "Prediction", "ms" };
	Statistic TearsInSecond { "Tears" };
	Statistic EarlyFrameCount { "EarlyFrameCount" };
	Statistic StaleFrameCount { "StaleFrameCount" };
	Statistic VSyncCount { "Swap Interval" };
	Statistic ExtraLatencyMode { "Extra Latency Mode" };
	Statistic FoveationLevel { "Foveation Level" };
	Statistic CpuLevel { "CPU Level (Main Core)" };
	Statistic GpuLevel { "GPU Level (Main Core)" };
	Statistic MemoryFrequency { "Memory Frequency", "MHz" };
	Statistic AvailableMemory { "Available Memory", "MB" };
	Statistic PowerLevel { "Power Level" };
	Statistic BatteryTemperature { "Battery Temperature", "C" };
	Statistic SensorTemperature { "Sensor Temperature", "C" };
	Statistic AppTime { "AppTime GPU Time", "ms" };
	Statistic GuardianTime { "Guardian GPU Time", "ms" };
	Statistic GpuCpu { "CPU & GPU Time", "ms" };
	Statistic LayerCount { "Layer Count", };
	Statistic GpuPercent { "GPU Utilization" };
	Statistic CpuPercentAverage { "Average CPU Utilization" };
	Statistic CpuPercentWorst { "Worst Core CPU Utilization" };
	Statistic DisplayProcessingUnit { "Display Processing Unit" };
	Statistic MinimumCompositorFrameLatency { "Minimum Compositor Frame Latency" };
	Statistic MaximumCompositorFrameLatency { "Maximum Compositor Frame Latency" };
	Statistic PercentileCompositorFrameLatency { "95th Percentile Compositor Frame Latency" };
	Statistic LocalDimming { "Local Dimming" };
	Statistic ScaleFactor { "Scale Factor" };
	Statistic LowPowerMode { "Low Power Mode" };

	void CalculateStatistics();
	std::vector<Statistic*> GetStatistics();
};