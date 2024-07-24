#pragma once
#include <memory>

#include "IParser.h"
#include "StatisticGroup.h"

class LogParserVrApi : public IParser
{
public:
	LogParserVrApi(std::shared_ptr<StatisticGroup> statisticGroup);

	void Parse(const std::string& logLine) const override;

	std::shared_ptr<StatisticGroup> statisticGroup;
};
