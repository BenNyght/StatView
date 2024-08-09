
#include "AdbCaptureGui.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>

#include "GuiDrawer.h"
#include "imgui.h"
#include "Adb/AdbUtility.h"
#include "imgui_stdlib.h"
#include "Adb/AdbLive.h"
#include "Adb/AdbVrApiCapture.h"

AdbCaptureGui::~AdbCaptureGui()
{
	AdbUtility::RestartAdb();
}

void AdbCaptureGui::Draw()
{
	bool open = true;
	ImGui::Begin(AdbCaptureGui::GuiName.c_str(), &open, ImGuiWindowFlags_NoCollapse);

	if (open == false)
	{
		ImGui::End();
		guiDrawer->RemoveDrawer<AdbCaptureGui>();
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

	CaptureLogcatButton();
	ImGui::SameLine();
	ClearLiveLogcatButton();

	LiveLogcatOutputView();

    ImGui::End();
}

void AdbCaptureGui::LiveLogcatOutputView()
{
	if (AdbVrApiCapture::VrApiLogcatExists() == false)
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

void AdbCaptureGui::CaptureLogcatButton()
{
	if (ImGui::Button("Capture"))
	{
		AdbVrApiCapture::CaptureLogcat();
	}
}

void AdbCaptureGui::ClearLiveLogcatButton()
{
	if (ImGui::Button("Clear Device Logcat"))
	{
		AdbVrApiCapture::ClearLogcatBuffer();
	}
}

std::string& AdbCaptureGui::GetName() const
{
	return GuiName;
}