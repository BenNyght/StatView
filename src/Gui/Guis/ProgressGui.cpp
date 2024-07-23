
#include "ProgressGui.h"

#include "imgui.h"
#include "Gui/ImGui/ImGuiExtensions.h"
#include "Progress/ProgressHandler.h"

void ProgressGui::Draw() const
{
	ImGui::Begin(ProgressGui::GuiName.c_str(), 0, 
		ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	if (ProgressHandler::ProgressItems.empty() == false)
	{
		std::string progressItems;
		for (auto& item : ProgressHandler::ProgressItems)
		{
			progressItems += item->DisplayText + " | ";
		}

		ImGui::LoadingText(progressItems.c_str());
	}
		
    ImGui::End();
}

std::string& ProgressGui::GetName() const
{
	return GuiName;
}