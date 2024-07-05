
#include "StatsGui.h"

#include <format>
#include <iomanip>
#include <sstream>

#include "imgui.h"
#include "Parsing/VrApiStatistics.h"

void StatsGui::Draw() const
{
	ImGui::ShowDemoWindow();

	ImGui::Begin(GuiName.c_str());

    static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

	auto statistics = VrApiStatistics::GetInstance().GetStatistics();

	if (ImGui::BeginTable("Stat Table", 9, flags))
	{
		ImGui::TableSetupColumn("Statistic");

		for (size_t i = 0; i < Statistic::GetIndexCount(); ++i)
		{
			ImGui::TableSetupColumn(Statistic::GetIndexName(i).c_str());
		}
		
		ImGui::TableHeadersRow();

		for (size_t statisticIndex = 0; statisticIndex < statistics.size(); ++statisticIndex)
		{
			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			auto statistic = statistics[statisticIndex];
			if (statistic.size == 0)
			{
				continue;
			}

			const bool itemIsSelected = Selection.contains(statisticIndex);
			ImGuiSelectableFlags selectableFlags =  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap;
            if (ImGui::Selectable(statistic.name.c_str(), itemIsSelected, selectableFlags))
            {
                if (ImGui::GetIO().KeyCtrl)
                {
                    if (itemIsSelected)
                    {
	                    Selection.find_erase_unsorted(statisticIndex);
                    }
                    else
                    {
	                    Selection.push_back(statisticIndex);
                    }
                }
                else
                {
                    Selection.clear();
                    Selection.push_back(statisticIndex);
                }
            }

			for (size_t column = 0; column < Statistic::GetIndexCount(); column++)
			{
				ImGui::TableNextColumn();

				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << statistic.GetIndexValue(column);
				std::string value = stream.str();
				ImGui::Text("%s", value.c_str());
			}
		}

		ImGui::EndTable();
	}

    ImGui::End();
}

std::string& StatsGui::GetName() const
{
	return GuiName;
}
