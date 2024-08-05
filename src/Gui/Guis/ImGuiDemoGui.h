#pragma once

#include <string>

#include "../Drawer.h"

class ImGuiDemoGui : public Drawer
{
public:
	ImGuiDemoGui();
	~ImGuiDemoGui();

	void Draw() override;
	std::string& GetName() const override;

	static inline std::string GuiName = "ImGui Demo Window";
};
