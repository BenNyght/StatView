
#include "PerformanceGraphGui.h"

#include "imgui.h"

int PerformanceGraphGui::instanceCount = 0;

PerformanceGraphGui::PerformanceGraphGui() : Drawer()
{
	statisticSelectionElement = std::make_shared<StatisticSelectionElement>();
	performanceStatsElement = std::make_shared<PerformanceStatsElement>();
	performanceGraphElement = std::make_shared<PerformanceGraphElement>(performanceStatsElement);

	instanceId = instanceCount;
	++instanceCount;
}

void PerformanceGraphGui::Draw() const
{
	ImGui::Begin(PerformanceGraphGui::GuiName.c_str());

	//statisticSelectionElement->Draw();

	performanceGraphElement->Draw();
	performanceStatsElement->Draw();
	
    ImGui::End();
}

std::string& PerformanceGraphGui::GetName() const
{
	return GuiName;
}