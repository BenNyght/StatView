
#include "ImGuiDemoGui.h"

#include <iostream>
#include <ostream>

#include "imgui.h"

ImGuiDemoGui::ImGuiDemoGui()
{
	std::cout << "ImGuiDemo Constructed" << std::endl;
}

ImGuiDemoGui::~ImGuiDemoGui()
{
	std::cout << "ImGuiDemo Deconstructed" << std::endl;
}

void ImGuiDemoGui::Draw() const
{
	ImGui::ShowDemoWindow();
}

std::string& ImGuiDemoGui::GetName() const
{
	return GuiName;
}