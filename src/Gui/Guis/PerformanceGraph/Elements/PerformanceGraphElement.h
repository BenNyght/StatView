#pragma once

#include "PerformanceStatsElement.h"
#include "VrApiStatistics.h"
#include "Captured/Statistic.h"
#include "Gui/Drawer.h"

class PerformanceGraphElement
{
public:
	PerformanceGraphElement(std::shared_ptr<PerformanceStatsElement> performanceStatsElement, std::shared_ptr<VrApiStatistics> statistics);
	void Draw();

private:
	void DrawGraphControls(bool& showLines, bool& showFills, float& fillRef, int& shadeMode);
	void DrawGraph(Statistic* statistic);

	std::shared_ptr<VrApiStatistics> statistics;
	std::shared_ptr<PerformanceStatsElement> performanceStatsElement;
};
