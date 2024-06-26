#pragma once
#include <iostream>

#include "Captured/Statistic.h"

// FPS={FPS},
// PredictionTime={Prediction}ms,
// TearsInSecond={Tears},
// EarlyFrameCount={EarlyFrameCount},
// StaleFrameCount={StaleFrameCount},
// VSnc={Swap Interval},
// LatencyMode={Extra Latency Mode},
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
	Statistic PredictionTime { "Prediction", "ms" };
	Statistic TearsInSecond { "Tears" };
	Statistic EarlyFrameCount { "EarlyFrameCount" };
	Statistic StaleFrameCount { "StaleFrameCount" };
	Statistic VSyncCount { "Swap Interval" };
	Statistic LatencyMode { "Extra Latency Mode" };
	Statistic FoveationLevel { "Foveation Level" };
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

	std::vector<Statistic> GetStatistics();

private:
	VrApiStatistics() {
        std::cout << "Singleton instance created!" << std::endl;
    }

    // Private destructor
    ~VrApiStatistics() {
        std::cout << "Singleton instance destroyed!" << std::endl;
    }
};