#pragma once
#include <iostream>

#include "Captured/Statistic.h"

// FPS={FPS},
// PredictionTime={Prediction}ms,
// TearsInSecond={Tears},
// EarlyFrameCount={EarlyFrameCount},
// StaleFrameCount={StaleFrameCount},
// VSnc={Swap Interval},
// ExtraLatencyMode={Extra Latency Mode},
// FoveationLevel={Foveation Level},
// CPU{Measured CPU Core}/GPU={CPU Level}/{GPU Level}, - TODO Map Individual CPU and GPU
// {CPU Frequency}/{GPU Frequency}MHz, - TODO Map Individual CPU and GPU
// OC={Online Core Mask},
// TA={TimeWarp Thread Affinity}/{Main Thread Affinity}/{Render Thread Affinity}, - TODO Map Space Warp
// SP={Timewarp Scheduling Priority}/{Main Thread Scheduling Priority}/{Render Thread Scheduling Priority},  - TODO Map Space Warp
// MemoryFrequency={Memory Frequency}MHz,
// AvailableMemory={Available Memory}MB,
// PSM={Power Save Mode},
// PowerLevel={Power Level},
// Temp={Battery Temperature}C/{Sensor Temperature}C,
// TW={TimeWarp GPU Time}ms,  - TODO Map Space Warp
// AppTime={AppTime GPU Time}ms,
// GuardianTime={Guardian GPU Time}ms,
// CPU&GPU={CPU & GPU Time}ms,
// LayerCount={Layer Count},
// GPU%={GPU Utilization},
// CPU%={Average CPU Utilization}(W{Worst Core CPU Utilization})

class VrApiStatistics
{
public:
	VrApiStatistics(const VrApiStatistics&) = delete;
    VrApiStatistics& operator=(const VrApiStatistics&) = delete;

	static VrApiStatistics& GetInstance()
	{
		static VrApiStatistics instance;
		return instance;
	}

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

	std::vector<Statistic*> GetStatistics();

private:
	VrApiStatistics() {}
    ~VrApiStatistics() {}
};