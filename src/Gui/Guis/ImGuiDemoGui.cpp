
#include "ImGuiDemoGui.h"

#include "imgui.h"

void ImGuiDemoGui::Draw() const
{
	ImGui::ShowDemoWindow();
}

std::string& ImGuiDemoGui::GetName() const
{
	return GuiName;
}