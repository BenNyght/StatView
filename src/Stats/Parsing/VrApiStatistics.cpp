
#include "VrApiStatistics.h"

std::vector<Statistic> VrApiStatistics::GetStatistics()
{
	std::vector<Statistic> statistics {};
	statistics.push_back(Fps);
	statistics.push_back(PredictionTime);
	statistics.push_back(TearsInSecond);
	statistics.push_back(EarlyFrameCount);
	statistics.push_back(StaleFrameCount);
	statistics.push_back(VSyncCount);
	statistics.push_back(LatencyMode);
	statistics.push_back(FoveationLevel);
	statistics.push_back(MemoryFrequency);
	statistics.push_back(AvailableMemory);
	statistics.push_back(PowerLevel);
	statistics.push_back(BatteryTemperature);
	statistics.push_back(SensorTemperature);
	statistics.push_back(AppTime);
	statistics.push_back(GuardianTime);
	statistics.push_back(GpuCpu);
	statistics.push_back(LayerCount);
	statistics.push_back(GpuPercent);
	statistics.push_back(CpuPercentAverage);
	statistics.push_back(CpuPercentWorst);
	return statistics;
}
