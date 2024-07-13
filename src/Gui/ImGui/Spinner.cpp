
#include <cmath>
#include <imgui_internal.h>

#include "ImGuiExtensions.h"

namespace ImGui
{
	bool Spinner(const char* label, float radius, int thickness, const ImU32& color)
	{
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
        {
	        return false;
        }
        
        ImGuiContext& gui = *GImGui;
        const ImGuiStyle& style = gui.Style;
        const ImGuiID id = window->GetID(label);

        const ImVec2 pos = window->DC.CursorPos;
        const ImVec2 size((radius ) * 2, (radius + style.FramePadding.y) * 2);
        
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
        {
	        return false;
        }
        
        // Render
        window->DrawList->PathClear();

        constexpr int numSegments = 30;
        const int start = abs(ImSin(gui.Time*1.8f)*(numSegments-5));
        
        const float aMin = IM_PI * 2.0f * static_cast<float>(start) / static_cast<float>(numSegments);
        const float aMax = IM_PI * 2.0f * (static_cast<float>(numSegments)-3) / static_cast<float>(numSegments);

        const auto centre = ImVec2(pos.x+radius, pos.y+radius+style.FramePadding.y);
        
        for (int i = 0; i < numSegments; i++) 
        {
            const float a = aMin + (static_cast<float>(i) / static_cast<float>(numSegments)) * (aMax - aMin);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a+gui.Time*8) * radius, centre.y + ImSin(a+gui.Time*8) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);
    }
}
