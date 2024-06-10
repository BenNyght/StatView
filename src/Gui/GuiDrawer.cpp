
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

GuiDrawer::GuiDrawer()
{
    PerformanceStats::GenerateTestData();

    drawers.push_back(std::make_unique<MenuBarGui>());
    drawers.push_back(std::make_unique<PerformanceGraphGui>());
    drawers.push_back(std::make_unique<HelloWorldGui>());
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
    if (!dockSpaceSetup) {
        dockSpaceSetup = true;

        ImGui::DockBuilderRemoveNode(viewDockSpaceId);
        ImGui::DockBuilderAddNode(viewDockSpaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(viewDockSpaceId, ImGui::GetMainViewport()->Size);

        ImGuiID dockIdMain = viewDockSpaceId;

        ImGuiID dockIdLeft, dockIdRight;

        ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Left, 0.2f, &dockIdLeft, &dockIdRight);

        ImGui::DockBuilderGetNode(dockIdRight)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar; // Lock the performance gui in place
        ImGui::DockBuilderDockWindow(PerformanceGraphGui::GuiName.c_str(), dockIdRight);

        ImGui::DockBuilderDockWindow(HelloWorldGui::GuiName.c_str(), dockIdLeft);

        ImGui::DockBuilderFinish(dockIdMain); // Finish the docking setup
    }
}
