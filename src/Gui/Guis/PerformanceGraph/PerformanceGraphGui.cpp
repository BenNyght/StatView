
#include "PerformanceGraphGui.h"

#include "FileUtility.h"
#include "GuiDrawer.h"
#include "imgui.h"

int PerformanceGraphGui::instanceCount = 0;

PerformanceGraphGui::PerformanceGraphGui() : Drawer()
{
	instanceId = instanceCount;
	++instanceCount;

	parser = std::make_shared<LogParser>();
	statistics = parser->GetVrApiStatistics();

	performanceStatsElement = std::make_shared<PerformanceStatsElement>(statistics);
	performanceGraphElement = std::make_shared<PerformanceGraphElement>(performanceStatsElement, statistics);
}

void PerformanceGraphGui::Process(bool latest) const
{
	if (processed == false)
	{
		if (instanceId == 0 || latest)
		{
			parser->ProcessLatest();
		}
		else
		{
			std::string path = FileUtility::OpenFilePanel("Select Logcat File", "", { "txt", "logcat", "log" });
			parser->ProcessPath(path);
		}

		processed = true;
	}
}

void PerformanceGraphGui::Draw() const
{
	const auto instanceAsString = std::to_string(instanceId);
	bool open = true;
	ImGui::Begin((PerformanceGraphGui::GuiName + ": " + instanceAsString).c_str(), &open);

	performanceGraphElement->Draw();
	performanceStatsElement->Draw();
	
    ImGui::End();

	if (open == false)
	{
		guiDrawer->RemoveDrawer(this);
	}
}

std::string& PerformanceGraphGui::GetName() const
{
	return GuiName;
}