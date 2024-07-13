
#include "GuiDrawer.h"

#include <iostream>
#include <vector>
#include <memory>

#include "IDrawer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "Guis/MenuBarGui.h"
#include "Guis/ProgressGui.h"
#include "Guis/TabGui.h"
#include "Guis/GraphTable/PerformanceGraphGui.h"
#include "Guis/GraphTable/StatsGui.h"

GuiDrawer::GuiDrawer()
{
    AddDrawer<MenuBarGui>();
    AddDrawer<PerformanceGraphGui>();
    AddDrawer<StatsGui>();
    AddDrawer<TabGui>();
    AddDrawer<ProgressGui>();

    AddActiveDrawer<PerformanceGraphGui>();
    AddActiveDrawer<StatsGui>();
	AddActiveDrawer<ProgressGui>();
}

void GuiDrawer::Draw()
{
    SetupDockBuilder();

    for (const auto& drawer : activeDrawers) 
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

        ImGuiID dockIdUp;
        ImGuiID dockIdDown;

        ImGui::DockBuilderSplitNode(dockIdMain, ImGuiDir_Up, 0.5f, &dockIdDown, &dockIdUp);

        DockDrawer<PerformanceGraphGui>(dockIdUp, ImGuiDockNodeFlags_NoTabBar);
        DockDrawer<StatsGui>(dockIdDown, ImGuiDockNodeFlags_NoTabBar);

        ImGui::DockBuilderFinish(dockIdMain); // Finish the docking setup
    }
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
	drawers.push_back(std::make_shared<TDrawer>());
    ImGui::DockBuilderDockWindow(TDrawer::GuiName.c_str(), dockId);
}

template <typename TDrawer>
void GuiDrawer::AddDrawer()
{
	drawers.push_back(std::make_shared<TDrawer>());
}

template <typename TDrawer>
void GuiDrawer::AddActiveDrawer()
{
    for (const auto& drawer : activeDrawers) 
    {
        auto foundDrawer = dynamic_cast<TDrawer*>(drawer.get());
        if (foundDrawer != nullptr) 
        {
            return;
        }
    }

    for (const auto& drawer : drawers) 
    {
        auto foundDrawer = dynamic_cast<TDrawer*>(drawer.get());
        if (foundDrawer != nullptr) 
        {
            activeDrawers.push_back(drawer);
            break;
        }
    }
}

template <typename TDrawer>
void GuiDrawer::RemoveActiveDrawer()
{
	for (int i = 0; i < activeDrawers.size(); ++i)
	{
		auto foundDrawer = dynamic_cast<TDrawer*>(activeDrawers[i].get());
        if (foundDrawer != nullptr) 
        {
            activeDrawers.erase(activeDrawers.begin() + i);
        }
	}
}