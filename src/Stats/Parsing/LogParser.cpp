
#include "LogParser.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

#include "StatisticGroup.h"
#include "Parsers/LogParserVrApi.h"
#include "Progress/ProgressHandler.h"
#include "Utility/StringUtility.h"

LogParser::LogParser()
{
	std::cout << "Log Parsed Constructed" << std::endl;

	parsers.push_back(std::make_shared<LogParserVrApi>(statistics));
}

LogParser::~LogParser()
{
	std::cout << "Log Parsed Deconstructed" << std::endl;
}

void LogParser::ProcessLatest()
{
	ProcessPath(latestFilePath);
}

void LogParser::ProcessPath(std::string path)
{
	if (IsFileOpen())
	{
		CloseFile();
	}

	if (std::filesystem::exists(path) == false)
	{
		return;
	}

	if (Contains(path, latestFileName) == false)
	{
		std::filesystem::copy(path, latestFilePath, std::filesystem::copy_options::overwrite_existing);
	}

	OpenFile(path);
	ProgressHandler::AddProgressItem(progressItem);
}

std::shared_ptr<StatisticGroup> LogParser::GetVrApiStatistics()
{
	return statistics;
}

void LogParser::Update()
{
	constexpr int processCount = 300;

	parsingLine += processCount;
	const std::string progress = std::to_string(parsingLine);
	const std::string displayText = "Parsing Log -> Line ";
	progressItem->DisplayText = displayText + progress;

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

			for (std::shared_ptr<IParser> parser : parsers)
			{
				parser->Parse(logLine);
			}

			requiresCalculation = true;
		}
		else if (requiresCalculation)
		{
			statistics->CalculateStatistics();
			requiresCalculation = false;
			ProgressHandler::RemoveProgressItem(progressItem);
			CloseFile();
		}
	}
}

bool LogParser::IsFileOpen()
{
	return parsingLog.is_open();
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