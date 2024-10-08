#pragma once

namespace ImGui
{
	bool BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
	bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
	void LoadingText();
	void LoadingText(const char*);
	void Hyperlink(const char* label, const char* url);
}
