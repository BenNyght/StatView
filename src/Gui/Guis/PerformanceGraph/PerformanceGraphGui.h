#pragma once

#include <string>

#include "StatisticGroup.h"
#include "Elements/PerformanceGraphElement.h"
#include "Gui/Drawer.h"
#include "LogParser.h"

class PerformanceGraphGui : public Drawer
{
public:
	PerformanceGraphGui();

	void Process(bool latest);
	void Draw() override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Performance Graph";

private:
	std::shared_ptr<LogParser> parser;
	std::shared_ptr<StatisticGroup> statistics;

	std::shared_ptr<PerformanceGraphElement> performanceGraphElement;
	std::shared_ptr<PerformanceStatsElement> performanceStatsElement;

	mutable bool processed = false;

	static int instanceCount;
};
