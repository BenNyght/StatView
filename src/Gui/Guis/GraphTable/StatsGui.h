#pragma once

#include <imgui.h>
#include <string>

#include "Gui/Drawer.h"

class StatsGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Stats";
	static inline ImVector<size_t> Selection {};
};
