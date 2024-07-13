#pragma once

#include <imgui.h>
#include <string>

#include "../IDrawer.h"

class ProgressGui : public IDrawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Progress";
};
