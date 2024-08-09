
#include "AdbLiveGui.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>

#include "GuiDrawer.h"
#include "imgui.h"
#include "Adb/AdbUtility.h"
#include "imgui_stdlib.h"
#include "Adb/AdbLive.h"
#include "Adb/AdbValidation.h"

AdbLiveGui::~AdbLiveGui()
{
	AdbUtility::RestartAdb();
}

void AdbLiveGui::Draw()
{
	bool open = true;
	ImGui::Begin(AdbLiveGui::GuiName.c_str(), &open, ImGuiWindowFlags_NoCollapse);

	if (open == false)
	{
		ImGui::End();
		guiDrawer->RemoveDrawer<AdbLiveGui>();
		return;
	}

	constexpr float width = 400;
	constexpr float height = 200;
	ImVec2 windowSize = ImGui::GetWindowSize();
	if (windowSize.x < width || windowSize.y < height)
	{
		ImGui::SetWindowSize(ImVec2 { width, height });
	}

	ImGui::InputText("Target App", &targetApplication, ImGuiInputTextFlags_CharsNoBlank);

	LiveLogcatButton();
	ImGui::SameLine();
	ClearLiveLogcatButton();

	LiveLogcatOutputView();

    ImGui::End();
}

void AdbLiveGui::LiveLogcatOutputView()
{
	if (AdbLive::LiveLogcatExists() == false)
	{
		std::cout << "Failed to find Logcat file" << std::endl;
		return;
	}

	std::ifstream file(AdbLive::GetLiveLogcatPath());
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::TextUnformatted(content.c_str());

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
	{
        ImGui::SetScrollHereY(1.0f); // Auto-scroll
    }
    ImGui::EndChild();
}

void AdbLiveGui::LiveLogcatButton()
{
	if (ImGui::Button("Live Logcat"))
	{
		AdbLive::LiveLogcat();
	}
}

void AdbLiveGui::ClearLiveLogcatButton()
{
	if (ImGui::Button("Clear"))
	{
		AdbLive::ClearLiveLogcat();
	}
}

void AdbLiveGui::GetDevicesButton()
{
	if (ImGui::Button("Get Devices"))
	{
		if (AdbValidation::IsAdbInstalled() == false)
		{
			return;
		}

		auto devices = AdbValidation::GetConnectedDevices();
		for (auto [id, status] : devices)
		{
			std::cout << id << " -> " << status << std::endl;
		}
	}
}

std::string& AdbLiveGui::GetName() const
{
	return GuiName;
}