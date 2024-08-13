
#include <imgui.h>
#include <ObjectArray.h>

namespace ImGui
{
	void Hyperlink(const char* label, const char* url)
	{
	    // Change color to look like a hyperlink (typically blue)
	    ImVec4 linkColor(81.0f / 255, 171.0f / 255, 245.0f / 255, 1.0f);
	    ImGui::PushStyleColor(ImGuiCol_Text, linkColor);
	    
	    ImGui::TextUnformatted(label);

	    // Check if the mouse is hovering over the text
	    if (ImGui::IsItemHovered())
	    {
	        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

	        // Get the position and size of the text
	        ImVec2 textPos = ImGui::GetItemRectMin();
	        ImVec2 textSize = ImGui::GetItemRectSize();

	        // Draw underline
	        ImDrawList* drawList = ImGui::GetWindowDrawList();
	        drawList->AddLine(
	            ImVec2(textPos.x, textPos.y + textSize.y),
	            ImVec2(textPos.x + textSize.x, textPos.y + textSize.y),
	            ImGui::GetColorU32(linkColor)
	        );

	        // Check if the text was clicked
	        if (ImGui::IsItemClicked())
	        {
	            // Platform-specific code to open the URL
#if defined(_WIN32)
	            ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#elif defined(__APPLE__)
	            std::string command = "open " + std::string(url);
	            system(command.c_str());
#elif defined(__linux__)
	            std::string command = "xdg-open " + std::string(url);
	            system(command.c_str());
#endif
	        }
	    }

	    ImGui::PopStyleColor();
	}
}
