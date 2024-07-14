#pragma once

#include <imgui.h>
#include <string>

#include "../Drawer.h"

class ProgressGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Progress";
};
