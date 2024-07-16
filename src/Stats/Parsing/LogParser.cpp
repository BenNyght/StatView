
#include "LogParser.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

#include "Captured/Statistic.h"
#include "VrApiStatistics.h"
#include "Progress/ProgressHandler.h"
#include "Utility/StringUtility.h"

#define VR_API_KEY "VrApi"

void LogParser::ProcessLatest()
{
	if (parsingLog.is_open())
	{
		parsingLog.close();
	}

	OpenFile("resources/VrApi_TestFile.log");
	ProgressHandler::AddProgressItem(progressItem);
}

void LogParser::Update()
{
	constexpr int processCount = 300;
	// 06-14 22:00:33.011  2072 10406 I VrApi   : FPS=23/90,Prd=0ms,Tear=0,Early=0,Stale=1,Stale2/5/10/max=0/0/0/0,VSnc=1,Lat=-1,Fov=0,CPU4/GPU=2/4,2419/305MHz,OC=FF,TA=0/70/0,SP=N/F/N,Mem=2092MHz,Free=2901MB,PLS=0,Temp=29.2C/0.0C,TW=2.62ms,App=8.13ms,GD=0.00ms,CPU&GPU=0.00ms,LCnt=1(DR0,LM0),GPU%=0.33,CPU%=0.98(W1.00),DSF=1.00,CFL=-1000.00/-1000.00,ICFLp95=19.00,LD=0,SF=0.00,LP=0,DVFS=0

	parsingLine += processCount;
	const std::string progress = std::to_string(parsingLine);
	const std::string displayText = "Parsing Log -> Line ";
	progressItem->DisplayText = displayText + progress;

	VrApiStatistics* statistics = &VrApiStatistics::GetInstance();
	std::string logLine;
	bool requiresCalculation = false;
	for (int i = 0; i < processCount; ++i)
	{
		if (getline (parsingLog, logLine))
		{
			if (logLine.empty())
			{
				continue;
			}

	        if (Contains(logLine, VR_API_KEY))
	        {
		        ParseVrApi(logLine, statistics);
				requiresCalculation = true;
	        }
		}
		else if (requiresCalculation)
		{
			for (const auto& statistic : statistics->GetStatistics())
			{
				statistic->CalculateStatistic();
			}
			requiresCalculation = false;
			ProgressHandler::RemoveProgressItem(progressItem);
			CloseFile();
		}
	}
}

void LogParser::OpenFile(std::string path)
{
	CloseFile();

	if (path.empty())
	{
		return;
	}

	parsingPath = std::move(path);
	parsingLog.open(parsingPath.c_str());
	parsingLine = 0;
	std::cout << "LogParser" << "-> opening " << parsingPath << std::endl;
}

void LogParser::CloseFile()
{
	if (parsingPath.empty())
	{
		return;
	}

	parsingLog.close();
	std::cout << "LogParser" << "-> closing " << parsingPath << std::endl;
}

void LogParser::ParseVrApi(const std::string& logLine, VrApiStatistics* statistics)
{
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
			statistics->Fps.AddValue(value);
		}
		else if (rawName == "Prd")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->PredictionTime.AddValue(value);
		}
		else if (rawName == "Tear")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->TearsInSecond.AddValue(value);
		}
		else if (rawName == "Early")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->EarlyFrameCount.AddValue(value);
		}
		else if (rawName == "Stale")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->StaleFrameCount.AddValue(value);
		}
		else if (rawName == "VSnc")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->VSyncCount.AddValue(value);
		}
		else if (rawName == "Lat")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->ExtraLatencyMode.AddValue(value);
		}
		else if (rawName == "Fov")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->FoveationLevel.AddValue(value);
		}
		else if (rawName == "Mem")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "MHz");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->MemoryFrequency.AddValue(value);
		}
		else if (rawName == "Free")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "MB");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->AvailableMemory.AddValue(value);
		}
		else if (rawName == "PLS")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->PowerLevel.AddValue(value);
		}
		else if (rawName == "Temp")
		{
			std::vector<std::string> batteryTemperatureSplit = Split(rawEquals, "C/");
			const double batteryTemperature = std::strtod(batteryTemperatureSplit[0].c_str(), &end);
			statistics->BatteryTemperature.AddValue(batteryTemperature);

			std::vector<std::string> sensorTemperatureSplit = Split(batteryTemperatureSplit[1], "C");
			const double sensorTemperature = std::strtod(sensorTemperatureSplit[0].c_str(), &end);
			statistics->SensorTemperature.AddValue(sensorTemperature);
		}
		else if (rawName == "App")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->AppTime.AddValue(value);
		}
		else if (rawName == "GD")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->GuardianTime.AddValue(value);
		}
		else if (rawName == "CPU&GPU")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "ms");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->GpuCpu.AddValue(value);
		}
		else if (rawName == "LCnt")
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "(");
			const double value = std::strtod(splitRawEquals[0].c_str(), &end);
			statistics->LayerCount.AddValue(value);
		}
		else if (rawName == "GPU%")
		{
			const double value = std::strtod(rawEquals.c_str(), &end) * 100;
			statistics->GpuPercent.AddValue(value);
		}
		else if (rawName == "CPU%")
		{
			std::vector<std::string> averageCpuPercentSplit = Split(rawEquals, "(W");
			const double averageCpuPercent = std::strtod(averageCpuPercentSplit[0].c_str(), &end);
			statistics->CpuPercentAverage.AddValue(averageCpuPercent);

			std::vector<std::string> worstCpuPercentSplit = Split(averageCpuPercentSplit[1], ")");
			const double worstCpuPercent = std::strtod(worstCpuPercentSplit[0].c_str(), &end);
			statistics->CpuPercentWorst.AddValue(worstCpuPercent);
		}
		else if (rawName == "DSF")
		{
			const double value = std::strtod(rawEquals.c_str(), &end) * 100;
			statistics->DisplayProcessingUnit.AddValue(value);
		}
		else if (rawName == "CFL")
		{
			std::vector<std::string> frameLatencySplit = Split(rawEquals, "/");
			const double minimumLatency = std::strtod(frameLatencySplit[0].c_str(), &end);
			statistics->MinimumCompositorFrameLatency.AddValue(minimumLatency);

			const double maximumLatency = std::strtod(frameLatencySplit[1].c_str(), &end);
			statistics->MaximumCompositorFrameLatency.AddValue(maximumLatency);
		}
		else if (rawName == "ICFLp95")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->PercentileCompositorFrameLatency.AddValue(value);
		}
		else if (rawName == "LD")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->LocalDimming.AddValue(value);
		}
		else if (rawName == "SF")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->ScaleFactor.AddValue(value);
		}
		else if (rawName == "LP")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->LowPowerMode.AddValue(value);
		}
		else if (rawName == "ASW")
		{
			const double value = std::strtod(rawEquals.c_str(), &end);
			statistics->FpsWithASW.AddValue(value);
		}
		else if (Contains(statisticRawValue, "/GPU="))
		{
			std::vector<std::string> splitRawEquals = Split(rawEquals, "/");
			const double CPULevel = std::strtod(splitRawEquals[0].c_str(), &end);
			const double GPULevel = std::strtod(splitRawEquals[1].c_str(), &end);
			statistics->CpuLevel.AddValue(CPULevel);
			statistics->GpuLevel.AddValue(GPULevel);
		}
	}
}