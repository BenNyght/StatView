
#include "MenuBarGui.h"

#include "imgui.h"

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
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
