
#include "MenuBarGui.h"

#include "imgui.h"
#include "ImGuiDemoGui.h"
#include "LogParser.h"
#include "Adb/AdbCaptureGui.h"
#include "Gui/GuiDrawer.h"
#include "PerformanceGraph/PerformanceGraphGui.h"

void MenuBarGui::Draw()
{
	if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("File")) 
        {
            if (ImGui::MenuItem("Open Latest Log File"))
            {
                std::shared_ptr<PerformanceGraphGui> gui = guiDrawer->AddDrawer<PerformanceGraphGui>();
                gui->Process(true);
            }

            if (ImGui::MenuItem("Open Log File"))
            {
                std::shared_ptr<PerformanceGraphGui> gui = guiDrawer->AddDrawer<PerformanceGraphGui>();
                gui->Process(false);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows"))
        {
            if (ImGui::MenuItem("Adb Performance Capture"))
            {
                auto drawer = guiDrawer->GetDrawer<AdbCaptureGui>();
                if (drawer == nullptr)
                {
	                guiDrawer->AddDrawer<AdbCaptureGui>();
                }
                else
                {
	                guiDrawer->RemoveDrawer<AdbCaptureGui>();
                }
            }

            if (ImGui::MenuItem("ImGui Demo Window"))
            {
                auto drawer = guiDrawer->GetDrawer<ImGuiDemoGui>();
                if (drawer == nullptr)
                {
	                guiDrawer->AddDrawer<ImGuiDemoGui>();
                }
                else
                {
	                guiDrawer->ToggleDrawer<ImGuiDemoGui>();
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

std::string& MenuBarGui::GetName() const
{
	return GuiName;
}