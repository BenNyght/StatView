
#include "GuiDrawer.h"

#include <iostream>
#include <vector>
#include <memory>

#include "Drawer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Guis/ImGuiDemoGui.h"
#include "Guis/MenuBarGui.h"
#include "Guis/ProgressGui.h"
#include "Guis/TabGui.h"
#include "Guis/PerformanceGraph/PerformanceGraphGui.h"

void GuiDrawer::Draw()
{
    SetupGuis();
    SetupDockBuilder();

    for (const auto& activeDrawer : activeDrawers)
    {
	    activeDrawer->Draw();
    }
}

void GuiDrawer::SetupGuis()
{
    static bool guisSetup = false;
    if (guisSetup)
    {
	    return;
    }

    guisSetup = true;

	AddDrawer<MenuBarGui>();
    AddDrawer<PerformanceGraphGui>();
    AddDrawer<TabGui>();
    AddDrawer<ProgressGui>();
    AddDrawer<ImGuiDemoGui>();

    AddActiveDrawer<MenuBarGui>();
    AddActiveDrawer<PerformanceGraphGui>();
	AddActiveDrawer<ProgressGui>();
}

void GuiDrawer::SetupDockBuilder()
{
    ImGuiID viewDockSpaceId = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

    static bool dockSpaceSetup = false;
    if (dockSpaceSetup) 
    {
        return;
    }

    dockSpaceSetup = true;

    ImGui::DockBuilderRemoveNode(viewDockSpaceId);
    ImGui::DockBuilderAddNode(viewDockSpaceId, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(viewDockSpaceId, ImGui::GetMainViewport()->Size);

    ImGuiID dockIdMain = viewDockSpaceId;

    //ImGuiID dockIdUp;
    //ImGuiID dockIdDown;

    //ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Up, 0.5f, &dockIdDown, &dockIdUp);

    DockDrawer<PerformanceGraphGui>(dockIdMain, ImGuiDockNodeFlags_NoTabBar);
    //DockDrawer<StatsElement>(dockIdDown, ImGuiDockNodeFlags_NoTabBar);

    ImGui::DockBuilderFinish(dockIdMain); // Finish the docking setup
}

std::shared_ptr<GuiDrawer> GuiDrawer::GuiDrawerInstance()
{
	return shared_from_this();
}

template <typename TDrawer>
void GuiDrawer::DockDrawer(ImGuiID dockId, ImGuiDockNodeFlags dockFlags)
{
	ImGui::DockBuilderGetNode(dockId)->LocalFlags |= dockFlags; // Flags "ImGuiDockNodeFlags_NoTabBar" locks the GUI in place and undock-able
	ImGui::DockBuilderDockWindow(TDrawer::GuiName.c_str(), dockId);
}

template <typename TDrawer>
void GuiDrawer::AddDockedDrawer(ImGuiID dockId)
{
    std::shared_ptr<TDrawer> drawer = std::make_shared<TDrawer>();
    drawer->guiDrawer = GuiDrawerInstance();
	drawers.push_back(drawer);
    ImGui::DockBuilderDockWindow(TDrawer::GuiName.c_str(), dockId);
}

template <typename TDrawer>
void GuiDrawer::AddDrawer()
{
    std::shared_ptr<TDrawer> drawer = std::make_shared<TDrawer>();
    drawer->guiDrawer = GuiDrawerInstance();
	drawers.push_back(drawer);
}