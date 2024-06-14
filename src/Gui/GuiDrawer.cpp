
#include "GuiDrawer.h"

#include <vector>
#include <memory>

#include "IDrawer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "PerformanceStats.h"
#include "Guis/HelloWorldGui.h"
#include "Guis/PerformanceGraphGui.h"
#include "Guis/MenuBarGui.h"
#include "Guis/StatsGui.h"

GuiDrawer::GuiDrawer()
{
    PerformanceStats::GenerateTestData();

    drawers.push_back(std::make_unique<MenuBarGui>());
    drawers.push_back(std::make_unique<PerformanceGraphGui>());
    drawers.push_back(std::make_unique<StatsGui>());
}

void GuiDrawer::Draw() const
{
    SetupDockBuilder();

    for (const auto& drawer : drawers) 
    {
        drawer->Draw();
    }
}

void GuiDrawer::SetupDockBuilder()
{
    ImGuiID viewDockSpaceId = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

    static bool dockSpaceSetup = false;
    if (!dockSpaceSetup) 
    {
        dockSpaceSetup = true;

        ImGui::DockBuilderRemoveNode(viewDockSpaceId);
        ImGui::DockBuilderAddNode(viewDockSpaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(viewDockSpaceId, ImGui::GetMainViewport()->Size);

        ImGuiID dockIdMain = viewDockSpaceId;

        ImGuiID dockIdDown, dockIdUp;

        ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Up, 0.2f, &dockIdDown, &dockIdUp);

        ImGui::DockBuilderGetNode(dockIdUp)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar; // Lock the performance gui in place
        ImGui::DockBuilderDockWindow(PerformanceGraphGui::GuiName.c_str(), dockIdUp);

        ImGui::DockBuilderDockWindow(StatsGui::GuiName.c_str(), dockIdDown);

        ImGui::DockBuilderFinish(dockIdMain); // Finish the docking setup
    }
}
