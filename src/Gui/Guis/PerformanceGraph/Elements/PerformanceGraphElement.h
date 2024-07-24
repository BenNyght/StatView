#pragma once

#include "PerformanceStatsElement.h"
#include "StatisticGroup.h"
#include "Captured/Statistic.h"
#include "Gui/Drawer.h"

class PerformanceGraphElement
{
public:
	PerformanceGraphElement(std::shared_ptr<PerformanceStatsElement> performanceStatsElement, std::shared_ptr<StatisticGroup> statisticGroup);
	void Draw();

private:
	void DrawGraphControls(bool& showLines, bool& showFills, float& fillRef, int& shadeMode);
	void DrawGraph(Statistic& statistic);

	std::shared_ptr<StatisticGroup> statistics;
	std::shared_ptr<PerformanceStatsElement> performanceStatsElement;
};
