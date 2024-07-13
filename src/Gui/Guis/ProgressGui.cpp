
#include "ProgressGui.h"

#include <imgui_internal.h>

#include "imgui.h"
#include "Gui/ImGui/ImGuiExtensions.h"
#include "Progress/ProgressHandler.h"

void ProgressGui::Draw() const
{
	if (ProgressHandler::ProgressItems.empty())
	{
		return;
	}

	ImGui::Begin(ProgressGui::GuiName.c_str());
		ImGui::LoadingText();
		for (auto& item : ProgressHandler::ProgressItems)
		{
			ImGui::Text(item->DisplayText.c_str());
		}
    ImGui::End();
}

std::string& ProgressGui::GetName() const
{
	return GuiName;
}