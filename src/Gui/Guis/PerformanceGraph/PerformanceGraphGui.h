#pragma once

#include <string>

#include "Elements/PerformanceGraphElement.h"
#include "Elements/StatisticSelectionElement.h"
#include "Gui/Drawer.h"

class PerformanceGraphGui : public Drawer
{
public:
	PerformanceGraphGui();

	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Performance Graph";

private:
	std::shared_ptr<PerformanceGraphElement> performanceGraphElement;
	std::shared_ptr<PerformanceStatsElement> performanceStatsElement;
	std::shared_ptr<StatisticSelectionElement> statisticSelectionElement;

	static int instanceCount;
	int instanceId;
};
