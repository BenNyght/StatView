#pragma once

#include <imgui.h>
#include <string>

#include "Gui/IDrawer.h"

class StatsGui : public IDrawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Stats";
	static inline ImVector<size_t> Selection {};
};
