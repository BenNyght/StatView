
#include "StatsGui.h"

#include "imgui.h"

void StatsGui::Draw() const
{
	ImGui::ShowDemoWindow();

	ImGui::Begin(StatsGui::GuiName.c_str());

    static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

	if (ImGui::BeginTable("Stat Table", 9, flags))
	{
		ImGui::TableSetupColumn("Statistic");
		ImGui::TableSetupColumn("Minimum");
		ImGui::TableSetupColumn("Maximum");
		ImGui::TableSetupColumn("Average");
		ImGui::TableSetupColumn("Median");
		ImGui::TableSetupColumn("Standard Deviation");
		ImGui::TableSetupColumn("95th Percentile");
		ImGui::TableSetupColumn("99.5th Percentile");
		ImGui::TableSetupColumn("Stat Count");
		
		ImGui::TableHeadersRow();

		for (int row = 0; row < 5; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < 9; column++)
			{
				ImGui::TableNextColumn();
				ImGui::Text("1000.0");
			}
		}
		ImGui::EndTable();
	}

    ImGui::End();

}