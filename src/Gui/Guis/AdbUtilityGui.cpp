
#include "AdbUtilityGui.h"

#include <iostream>
#include <ostream>

#include "imgui.h"
#include "Adb/AdbUtility.h"
#include "imgui_stdlib.h"

std::string AdbUtilityGui::TargetApplication;

void AdbUtilityGui::Draw() const
{
	ImGui::Begin(AdbUtilityGui::GuiName.c_str());

	constexpr float width = 400;
	constexpr float height = 200;
	ImVec2 windowSize = ImGui::GetWindowSize();
	if (windowSize.x < width || windowSize.y < height)
	{
		ImGui::SetWindowSize(ImVec2 { width, height });
	}

	ImGui::InputText("Target App", &TargetApplication, ImGuiInputTextFlags_CharsNoBlank);
	if (TargetApplication.empty())
	{
		ImGui::Spacing();
		ImGui::Text("Target App Required");
		ImGui::End();
		return;
	}

	if (ImGui::Button("Get Devices"))
	{
		auto devices = AdbUtility::GetConnectedDevices();
		for (auto [id, status] : devices)
		{
			std::cout << id << " -> " << status << std::endl;
		}
	}

    ImGui::End();
}

std::string& AdbUtilityGui::GetName() const
{
	return GuiName;
}