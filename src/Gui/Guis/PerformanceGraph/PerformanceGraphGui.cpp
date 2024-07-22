
#include "PerformanceGraphGui.h"

#include "FileUtility.h"
#include "imgui.h"

int PerformanceGraphGui::instanceCount = 0;

PerformanceGraphGui::PerformanceGraphGui() : Drawer()
{
	std::string path = FileUtility::OpenFilePanel("Select Logcat File", "", { "txt", "logcat", "log" });
	parser = std::make_shared<LogParser>();
    parser->ProcessPath(path);
	statistics = parser->GetVrApiStatistics();

	statisticSelectionElement = std::make_shared<StatisticSelectionElement>();
	performanceStatsElement = std::make_shared<PerformanceStatsElement>(statistics);
	performanceGraphElement = std::make_shared<PerformanceGraphElement>(performanceStatsElement, statistics);

	instanceId = instanceCount;
	++instanceCount;
}

void PerformanceGraphGui::Draw() const
{
	const auto instanceAsString = std::to_string(instanceId);
	ImGui::Begin((PerformanceGraphGui::GuiName + instanceAsString).c_str());

	//statisticSelectionElement->Draw();

	performanceGraphElement->Draw();
	performanceStatsElement->Draw();
	
    ImGui::End();
}

std::string& PerformanceGraphGui::GetName() const
{
	return GuiName;
}