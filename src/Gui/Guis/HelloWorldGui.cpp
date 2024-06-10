
#include "HelloWorldGui.h"

#include "imgui.h"

void HelloWorldGui::Draw() const
{
	ImGui::Begin(HelloWorldGui::GuiName.c_str());
    ImGui::Text("This is some useful text.");
    ImGui::End();
}
