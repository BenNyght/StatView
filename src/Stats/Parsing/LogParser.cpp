
#include "LogParser.h"
#include <string>
#include <iostream>
#include <fstream>

#include "Captured/Statistic.h"
#include "VrApiStatistics.h"

void LogParser::ParseLatest()
{
	std::string logLine;
	std::ifstream latestVrApiLog("resources/VrApi_TestFile.log");

	auto& fps = VrApiStatistics::GetInstance().Fps;

	while (getline (latestVrApiLog, logLine)) 
	{
		if (logLine.empty() || logLine.find("FPS") == std::string::npos) 
		{
			continue;
		}

        size_t position = logLine.find("FPS");
        std::string trimmedLine = logLine.substr(position);

		std::vector<std::string> statisticRawValues = Split(trimmedLine, ",");
		for (const std::string& statisticRawValue : statisticRawValues)
		{
			std::vector<std::string> split = Split(statisticRawValue, "=");
			std::vector<std::string> fpsValue = Split(split[1], "/");

			double value = atof(fpsValue[0].c_str());
			if (value > 40)
			{
				fps.AddValue(value);
			}
			break;
		}
	}

	std::cout << "Stats " << std::endl;
	std::cout << "Max: " << fps.max << std::endl;
	std::cout << "Min: " << fps.min << std::endl;
	std::cout << "Average: " << fps.average << std::endl;

	// Close the file
    latestVrApiLog.close();
}

std::vector<std::string> LogParser::Split(const std::string& search, const std::string& delimiter)
{
    size_t startPosition = 0;
	size_t endPosition;
    const size_t delimiterLength = delimiter.length();

    std::vector<std::string> result;

    while ((endPosition = search.find(delimiter, startPosition)) != std::string::npos) 
	{
        std::string token = search.substr (startPosition, endPosition - startPosition);
        startPosition = endPosition + delimiterLength;
        result.push_back (token);
    }

    result.push_back (search.substr (startPosition));
    return result;
}

bool LogParser::Contains(const std::string& search, const std::string& contains)
{
	if (search.find(contains) != std::string::npos) 
	{
	    return true;
	}

	return false;
}