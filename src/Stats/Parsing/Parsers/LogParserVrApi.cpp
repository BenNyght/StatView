
#include "LogParserVrApi.h"
#include "StringUtility.h"

#define VR_API_KEY "VrApi"

enum Statistic_VrApi : int
{
	Statistic_VrApi_Fps,
	Statistic_VrApi_FpsWithASW,
	Statistic_VrApi_PredictionTime,
	Statistic_VrApi_TearsInSecond,
	Statistic_VrApi_EarlyFrameCount,
	Statistic_VrApi_StaleFrameCount,
	Statistic_VrApi_VSyncCount,
	Statistic_VrApi_ExtraLatencyMode,
	Statistic_VrApi_FoveationLevel,
	Statistic_VrApi_CpuLevel,
	Statistic_VrApi_GpuLevel,
	Statistic_VrApi_MemoryFrequency,
	Statistic_VrApi_AvailableMemory,
	Statistic_VrApi_PowerLevel,
	Statistic_VrApi_BatteryTemperature,
	Statistic_VrApi_SensorTemperature,
	Statistic_VrApi_AppTime,
	Statistic_VrApi_GuardianTime,
	Statistic_VrApi_GpuCpuTime,
	Statistic_VrApi_LayerCount,
	Statistic_VrApi_GpuPercent,
	Statistic_VrApi_CpuPercentAverage,
	Statistic_VrApi_CpuPercentWorst,
	Statistic_VrApi_DisplayProcessingUnit,
	Statistic_VrApi_MinimumCompositorFrameLatency,
	Statistic_VrApi_MaximumCompositorFrameLatency,
	Statistic_VrApi_PercentileCompositorFrameLatency,
	Statistic_VrApi_LocalDimming,
	Statistic_VrApi_ScaleFactor,
	Statistic_VrApi_LowPowerMode,
	Last,
};

LogParserVrApi::LogParserVrApi(std::shared_ptr<StatisticGroup> statisticGroup) : statisticGroup(statisticGroup)
{
	auto& statistics = statisticGroup->statistics;

	statistics.resize(Statistic_VrApi::Last);
	statistics[Statistic_VrApi_Fps] = { "FPS" };
	statistics[Statistic_VrApi_FpsWithASW] = { "FPS w/Generated Frames" };
	statistics[Statistic_VrApi_PredictionTime] = { "Prediction", "ms" };
	statistics[Statistic_VrApi_TearsInSecond] = { "Tears" };
	statistics[Statistic_VrApi_EarlyFrameCount] = { "EarlyFrameCount" };
	statistics[Statistic_VrApi_StaleFrameCount] = { "StaleFrameCount" };
	statistics[Statistic_VrApi_VSyncCount] = { "Swap Interval" };
	statistics[Statistic_VrApi_ExtraLatencyMode] = { "Extra Latency Mode" };
	statistics[Statistic_VrApi_FoveationLevel] = { "Foveation Level" };
	statistics[Statistic_VrApi_CpuLevel] = { "CPU Level (Main Core)" };
	statistics[Statistic_VrApi_GpuLevel] = { "GPU Level (Main Core)" };
	statistics[Statistic_VrApi_MemoryFrequency] = { "Memory Frequency", "MHz" };
	statistics[Statistic_VrApi_AvailableMemory] = { "Available Memory", "MB" };
	statistics[Statistic_VrApi_PowerLevel] = { "Power Level" };
	statistics[Statistic_VrApi_BatteryTemperature] = { "Battery Temperature", "C" };
	statistics[Statistic_VrApi_SensorTemperature] = { "Sensor Temperature", "C" };
	statistics[Statistic_VrApi_AppTime] = { "AppTime GPU Time", "ms" };
	statistics[Statistic_VrApi_GuardianTime] = { "Guardian GPU Time", "ms" };
	statistics[Statistic_VrApi_GpuCpuTime] = { "CPU & GPU Time", "ms" };
	statistics[Statistic_VrApi_LayerCount] = { "Layer Count", };
	statistics[Statistic_VrApi_GpuPercent] = { "GPU Utilization" };
	statistics[Statistic_VrApi_CpuPercentAverage] = { "Average CPU Utilization" };
	statistics[Statistic_VrApi_CpuPercentWorst] = { "Worst Core CPU Utilization" };
	statistics[Statistic_VrApi_DisplayProcessingUnit] = { "Display Processing Unit" };
	statistics[Statistic_VrApi_MinimumCompositorFrameLatency] = { "Minimum Compositor Frame Latency" };
	statistics[Statistic_VrApi_MaximumCompositorFrameLatency] = { "Maximum Compositor Frame Latency" };
	statistics[Statistic_VrApi_PercentileCompositorFrameLatency] = { "95th Percentile Compositor Frame Latency" };
	statistics[Statistic_VrApi_LocalDimming] = { "Local Dimming" };
	statistics[Statistic_VrApi_ScaleFactor] = { "Scale Factor" };
	statistics[Statistic_VrApi_LowPowerMode] = { "Low Power Mode" };
}

void LogParserVrApi::Parse(const std::string& logLine) const
{
	if (Contains(logLine, VR_API_KEY) == false)
    {
        return;
    }

	// Remove info before FPS
	size_t position = logLine.find("FPS");
    std::string trimmedLine = logLine.substr(position);

	std::vector<std::string> statisticRawValues = Split(trimmedLine, ",");
	for (const std::string& statisticRawValue : statisticRawValues)
	{
		if (Contains(statisticRawValue, "=") == false)
		{
			continue;
		}

		std::vector<std::string> split = Split(statisticRawValue, "=");
		std::string rawName = split[0];
		std::string rawEquals = split[1];
		char* end;
		if (rawName == "FPS")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "/");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_Fps].AddValue(value);
		}
		else if (rawName == "Prd")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_PredictionTime].AddValue(value);
		}
		else if (rawName == "Tear")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_TearsInSecond].AddValue(value);
		}
		else if (rawName == "Early")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_EarlyFrameCount].AddValue(value);
		}
		else if (rawName == "Stale")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_StaleFrameCount].AddValue(value);
		}
		else if (rawName == "VSnc")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_VSyncCount].AddValue(value);
		}
		else if (rawName == "Lat")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_ExtraLatencyMode].AddValue(value);
		}
		else if (rawName == "Fov")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_FoveationLevel].AddValue(value);
		}
		else if (rawName == "Mem")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "MHz");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_MemoryFrequency].AddValue(value);
		}
		else if (rawName == "Free")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "MB");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_AvailableMemory].AddValue(value);
		}
		else if (rawName == "PLS")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_PowerLevel].AddValue(value);
		}
		else if (rawName == "Temp")
		{
			std::vector<std::string> batteryTemperatureSplit = Split(rawEquals, "C/");
			const double batteryTemperature = std::strtod(batteryTemperatureSplit[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_BatteryTemperature].AddValue(batteryTemperature);

			std::vector<std::string> sensorTemperatureSplit = Split(batteryTemperatureSplit[1], "C");
			const double sensorTemperature = std::strtod(sensorTemperatureSplit[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_SensorTemperature].AddValue(sensorTemperature);
		}
		else if (rawName == "App")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_AppTime].AddValue(value);
		}
		else if (rawName == "GD")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_GuardianTime].AddValue(value);
		}
		else if (rawName == "CPU&GPU")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_GpuCpuTime].AddValue(value);
		}
		else if (rawName == "LCnt")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "(");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_LayerCount].AddValue(value);
		}
		else if (rawName == "GPU%")
		{
			const double value = std::strtod(rawEquals.c_str(), &end) * 100;
			statisticGroup->statistics[Statistic_VrApi_GpuPercent].AddValue(value);
		}
		else if (rawName == "CPU%")
		{
			std::vector<std::string> averageCpuPercentSplit = Split(rawEquals, "(W");
			const double averageCpuPercent = std::strtod(averageCpuPercentSplit[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_CpuPercentAverage].AddValue(averageCpuPercent);

			std::vector<std::string> worstCpuPercentSplit = Split(averageCpuPercentSplit[1], ")");
			const double worstCpuPercent = std::strtod(worstCpuPercentSplit[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_CpuPercentAverage].AddValue(worstCpuPercent);
		}
		else if (rawName == "DSF")
		{
			const double value = std::strtod(rawEquals.c_str(), &end) * 100;
			statisticGroup->statistics[Statistic_VrApi_DisplayProcessingUnit].AddValue(value);
		}
		else if (rawName == "CFL")
		{
			std::vector<std::string> frameLatencySplit = Split(rawEquals, "/");
			const double minimumLatency = std::strtod(frameLatencySplit[0].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_MinimumCompositorFrameLatency].AddValue(minimumLatency);

			const double maximumLatency = std::strtod(frameLatencySplit[1].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_MaximumCompositorFrameLatency].AddValue(maximumLatency);
		}
		else if (rawName == "ICFLp95")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_PercentileCompositorFrameLatency].AddValue(value);
		}
		else if (rawName == "LD")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_LocalDimming].AddValue(value);
		}
		else if (rawName == "SF")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_ScaleFactor].AddValue(value);
		}
		else if (rawName == "LP")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_LowPowerMode].AddValue(value);
		}
		else if (rawName == "ASW")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_FpsWithASW].AddValue(value);
		}
		else if (Contains(statisticRawValue, "/GPU="))
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "/");
			const double CPULevel = std::strtod(splitRawEquals[0].c_str(), &end);
			const double GPULevel = std::strtod(splitRawEquals[1].c_str(), &end);
			statisticGroup->statistics[Statistic_VrApi_CpuLevel].AddValue(CPULevel);
			statisticGroup->statistics[Statistic_VrApi_GpuLevel].AddValue(GPULevel);
		}
	}
}
