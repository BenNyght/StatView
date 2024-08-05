
#include "AdbUtilityGui.h"

#include <deque>
#include <fstream>
#include <iostream>
#include <ostream>

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
	ImGui::InputInt("Max Line Count", &targetLineCount, 10);
    if (targetLineCount < 1)
    {
	    targetLineCount = 1;
    }

	LiveLogcatButton();
	ImGui::SameLine();
	ClearLiveLogcatButton();

	ReadLog();
	LiveLogcatOutputView();

    ImGui::End();
}

void AdbUtilityGui::ReadLog()
{
    const int bufferSize = 4096; // Buffer size for reading file chunks
    std::ifstream file(AdbUtility::GetLiveLogcatPath(), std::ios::binary);

    if (!file.is_open()) 
    {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    liveLog.clear();
    std::string leftover;
    std::vector<char> buffer(bufferSize);

    file.seekg(0, std::ios::end);
    std::streampos filePos = file.tellg();

    while (filePos > 0 && liveLog.size() < targetLineCount) 
    {
        int readSize = std::min(bufferSize, static_cast<int>(filePos));
        filePos -= readSize;
        file.seekg(filePos);
        file.read(buffer.data(), readSize);

        for (int i = readSize - 1; i >= 0; --i) 
        {
            if (buffer[i] == '\n' || buffer[i] == '\r') 
            {
                std::string line = leftover;
                if (i != readSize - 1) 
                {
                    line.insert(line.begin(), buffer.begin() + i + 1, buffer.begin() + readSize);
                }

                if (!line.empty()) 
                {
                    liveLog.push_front(line);
                    leftover.clear();
                }
            } 
            else 
            {
                leftover.insert(leftover.begin(), buffer[i]);
            }

            if (liveLog.size() == targetLineCount) 
            {
                break;
            }
        }
    }

    if (!leftover.empty() && liveLog.size() < targetLineCount) 
    {
        liveLog.push_front(leftover);
    }

    std::cout << liveLog.size() << std::endl;

    file.close();
}

void AdbUtilityGui::LiveLogcatOutputView()
{
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto& log : liveLog)
	{
        ImGui::TextUnformatted(log.c_str());
    }

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
		liveLog.clear();
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

std::string& AdbUtilityGui::GetName() const
{
	return GuiName;
}