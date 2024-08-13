
#include "PerformanceStatsElement.h"

#include <format>
#include <iomanip>
#include <sstream>

#include "imgui.h"
#include "StatisticGroup.h"

PerformanceStatsElement::PerformanceStatsElement(std::shared_ptr<StatisticGroup> statistics) : statisticGroup(statistics)
{

}

void PerformanceStatsElement::Draw() const
{
    static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

    const auto& allStatistics = statisticGroup->statistics;

	if (ImGui::BeginTable("Stat Table", 9, flags))
	{
		ImGui::TableSetupColumn("Statistic");

		for (size_t i = 0; i < Statistic::GetIndexCount(); ++i)
		{
			ImGui::TableSetupColumn(Statistic::GetIndexName(i).c_str());
		}
		
		ImGui::TableHeadersRow();

		for (size_t statisticIndex = 0; statisticIndex < allStatistics.size(); ++statisticIndex)
		{
			auto& statistic = allStatistics[statisticIndex];
			if (statistic.size == 0)
			{
				continue;
			}

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			const bool itemIsSelected = selection.contains(statisticIndex);
			ImGuiSelectableFlags selectableFlags =  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap;
            if (ImGui::Selectable(statistic.name.c_str(), itemIsSelected, selectableFlags))
            {
                if (ImGui::GetIO().KeyCtrl)
                {
                    if (itemIsSelected)
                    {
	                    selection.find_erase_unsorted(statisticIndex);
                    }
                    else
                    {
	                    selection.push_back(statisticIndex);
                    }
                }
                else
                {
                    selection.clear();
                    selection.push_back(statisticIndex);
                }
            }

			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
			{
				ImGui::BeginTooltip();
				ImGui::SetWindowSize(ImVec2 { 200, 300 });
				ImGui::Text(statistic.description.c_str());
				ImGui::EndTooltip();
			}

			for (size_t column = 0; column < Statistic::GetIndexCount(); column++)
			{
				ImGui::TableNextColumn();

				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << statistic.GetIndexValue(column);
				ImGui::Text("%s", stream.str().c_str());
			}
		}

		ImGui::EndTable();
	}
}
