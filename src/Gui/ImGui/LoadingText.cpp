
#include <format>
#include <imgui.h>
#include <string>

#include "ImGuiExtensions.h"

namespace ImGui
{
	void LoadingText()
	{
		ImGui::Text("Loading %c", "|/-\\"[static_cast<int>(ImGui::GetTime() / 0.05f) & 3]);
	}

	void LoadingText(const char* suffix)
	{
		ImGui::Text("Loading %c %s", "|/-\\"[static_cast<int>(ImGui::GetTime() / 0.05f) & 3], suffix);
	}
}
