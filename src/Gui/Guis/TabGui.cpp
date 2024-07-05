
#include "TabGui.h"

#include <iostream>
#include "imgui.h"

void TabGui::Draw() const
{
	if (ImGui::Button("Graph", ImVec2 { 400, 100 }))
	{
		std::cout << "Button Down" << std::endl;
	}
}

std::string& TabGui::GetName() const
{
	return GuiName;
}