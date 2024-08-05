
#include "HomePageGui.h"

#include "imgui.h"

void HomePageGui::Draw()
{
	ImGui::Begin(HomePageGui::GuiName.c_str());
	ImGui::Text("Oh Hey");
	ImGui::Text("Should probably put something here... eh, you'll figure it out");
    ImGui::End();
}

std::string& HomePageGui::GetName() const
{
	return GuiName;
}