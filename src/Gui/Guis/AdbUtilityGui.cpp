
#include "AdbUtilityGui.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>

#include "GuiDrawer.h"
#include "imgui.h"
#include "Adb/AdbUtility.h"
#include "imgui_stdlib.h"

AdbUtilityGui::~AdbUtilityGui()
{
	AdbUtility::RestartAdb();
}

void AdbUtilityGui::Draw()
{
	bool open = true;
	ImGui::Begin(AdbUtilityGui::GuiName.c_str(), &open, ImGuiWindowFlags_NoCollapse);

	if (open == false)
	{
		ImGui::End();
		guiDrawer->RemoveDrawer<AdbUtilityGui>();
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

void AdbUtilityGui::LiveLogcatOutputView()
{
	if (AdbUtility::LiveLogcatExists() == false)
	{
		std::cout << "Failed to find Logcat file" << std::endl;
		return;
	}

	std::ifstream file(AdbUtility::GetLiveLogcatPath());
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

void AdbUtilityGui::LiveLogcatButton()
{
	if (ImGui::Button("Live Logcat"))
	{
		AdbUtility::LiveLogcat();
	}
}

void AdbUtilityGui::ClearLiveLogcatButton()
{
	if (ImGui::Button("Clear"))
	{
		AdbUtility::ClearLiveLogcat();
	}
}

void AdbUtilityGui::GetDevicesButton()
{
	if (ImGui::Button("Get Devices"))
	{
		if (AdbUtility::IsAdbSetup() == false)
		{
			return;
		}

		auto devices = AdbUtility::GetConnectedDevices();
		for (auto [id, status] : devices)
		{
			std::cout << id << " -> " << status << std::endl;
		}
	}
}

char AdbUtilityGui::GetLogcatPriority(const std::string& logLine)
{
    // Define a regex pattern to match the logcat format and capture the priority
    std::regex logPattern(R"(^\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}\.\d{3}\s+\d+\s+\d+\s+([VDIWEFS]))");
    std::smatch matches;

    // Use regex to search for the pattern in the log line
    if (std::regex_search(logLine, matches, logPattern))
    {
        // matches[1] contains the priority level
        if (matches.size() > 1)
        {
            return matches[1].str()[0];
        }
    }

    // Return a default value if no valid priority is found
    return '?';
}

std::string& AdbUtilityGui::GetName() const
{
	return GuiName;
}