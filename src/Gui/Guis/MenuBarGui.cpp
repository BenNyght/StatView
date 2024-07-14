
#include "MenuBarGui.h"

#include "imgui.h"
#include "ImGuiDemoGui.h"
#include "Gui/GuiDrawer.h"

void MenuBarGui::Draw() const
{
	if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("Windows")) 
        {
            if (ImGui::MenuItem("Open New Window")) 
            {
                // Handle opening a new window (set a flag or call a function to open a window)
            }

            if (ImGui::MenuItem("ImGui Demo Window")) 
            {
                guiDrawer->ToggleActiveDrawer<ImGuiDemoGui>();
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