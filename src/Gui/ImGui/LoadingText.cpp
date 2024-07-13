
#include <imgui.h>

#include "ImGuiExtensions.h"

namespace ImGui
{
	void LoadingText()
	{
		ImGui::Text("Loading %c", "|/-\\"[static_cast<int>(ImGui::GetTime() / 0.05f) & 3]);
	}
}
