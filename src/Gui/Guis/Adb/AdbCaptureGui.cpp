
#include "AdbCaptureGui.h"

#include <iostream>
#include <ostream>
#include <regex>

#include "GuiDrawer.h"
#include "imgui.h"
#include "Timer.h"
#include "Adb/AdbValidation.h"
#include "Adb/AdbVrApiCapture.h"

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

	constexpr float width = 600;
	constexpr float height = 200;
	ImVec2 windowSize = ImGui::GetWindowSize();
	if (windowSize.x < width || windowSize.y < height)
	{
		ImGui::SetWindowSize(ImVec2 { width, height });
	}

	ImGui::Text("This window allows you to capture a performance log for a chosen duration.");
	ImGui::Text("Ensure the headset remains connected for the duration of the capture.");
	ImGui::Text("Once the capture is complete you can save the file and view it in the\nperformance graph viewer.");

	ImGui::Spacing();

	const char* items[] = { "30 sec", "60 sec", "3 min", "5 min", "10 min", "30 min", "45 min", "60 min" };
	const std::vector<double> duration = { 30, 60, 180, 300, 600, 1800, 2700, 3600 };

	static int currentItem = 4;
	static Timer timer {};
	static bool capturing = false;
	static bool failedToFindDevice = false;

	if (capturing == false)
	{
		if (ImGui::BeginCombo("##combo", items[currentItem]))
		{
			for (int i = 0; i < IM_ARRAYSIZE(items); i++)
		    {
				const bool isSelected = (items[currentItem] == items[i]);
		        if (ImGui::Selectable(items[i], isSelected))
		        {
					currentItem = i;
		        }
		            
		        if (isSelected)
		        {
			        ImGui::SetItemDefaultFocus();
		        }
		    }
		    ImGui::EndCombo();
		}
		ImGui::SameLine();

		if (ImGui::Button("Start Capturing"))
		{
			if (AdbValidation::IsDeviceAvailable() == false)
		    {
				std::cout << "Device not found." << std::endl;
				failedToFindDevice = true;
		    }
			else
			{
				timer.Start();
				AdbVrApiCapture::ClearLogcatBuffer();
				capturing = true;
				failedToFindDevice = false;
			}			
		}

		if (failedToFindDevice)
		{
			ImGui::Text("Failed to find device. Please try again.");
		}
	}
	else
	{
		double currentTime = timer.ElapsedSeconds();
		double totalTime = duration[currentItem];

		if (currentTime >= totalTime)
		{
			std::cout << "Finished capturing file. Captured for " << currentTime << "seconds" << std::endl;
			timer.Stop();
			AdbVrApiCapture::CaptureVrApi();
			capturing = false;
		}
		else
		{
			if (ImGui::Button("Stop Capturing"))
			{
				std::cout << "Finished capturing file. Captured for " << currentTime << "seconds" << std::endl;
				timer.Stop();
				AdbVrApiCapture::CaptureVrApi();
				capturing = false;
			}

			std::ostringstream overlayStream;
			overlayStream.precision(1);
			overlayStream << std::fixed << currentTime << "s / " << totalTime << "s";
			ImGui::ProgressBar(currentTime / totalTime, ImVec2(-1, 0), overlayStream.str().c_str());
		}
	}

    ImGui::End();
}

std::string& AdbCaptureGui::GetName() const
{
	return GuiName;
}