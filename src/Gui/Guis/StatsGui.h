#pragma once

#include <imgui.h>
#include <string>

#include "../IDrawer.h"

class StatsGui : public IDrawer
{
public:
	void Draw() const override;

	static inline std::string GuiName = "Stats";
	static inline ImVector<size_t> Selection {};
};
