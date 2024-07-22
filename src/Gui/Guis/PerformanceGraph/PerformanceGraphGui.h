#pragma once

#include <string>

#include "VrApiStatistics.h"
#include "Elements/PerformanceGraphElement.h"
#include "Elements/StatisticSelectionElement.h"
#include "Gui/Drawer.h"
#include "LogParser.h"

class PerformanceGraphGui : public Drawer
{
public:
	PerformanceGraphGui();

	void SetStatistics(VrApiStatistics statistics);

	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Performance Graph";

private:
	std::shared_ptr<LogParser> parser;
	std::shared_ptr<VrApiStatistics> statistics;

	std::shared_ptr<PerformanceGraphElement> performanceGraphElement;
	std::shared_ptr<PerformanceStatsElement> performanceStatsElement;
	std::shared_ptr<StatisticSelectionElement> statisticSelectionElement;

	static int instanceCount;
};
