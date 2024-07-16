
#include "PerformanceGraphGui.h"

#include "imgui.h"

PerformanceGraphGui::PerformanceGraphGui() : Drawer()
{
	performanceStatsElement = std::make_shared<PerformanceStatsElement>();
	performanceGraphElement = std::make_shared<PerformanceGraphElement>(performanceStatsElement);
}

void PerformanceGraphGui::Draw() const
{
	ImGui::Begin(PerformanceGraphGui::GuiName.c_str());

	performanceGraphElement->Draw();
	performanceStatsElement->Draw();
	
    ImGui::End();
}

std::string& PerformanceGraphGui::GetName() const
{
	return GuiName;
}