
#include "HelloWorldGui.h"

#include "imgui.h"

void HelloWorldGui::Draw() const
{
	ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();
}
