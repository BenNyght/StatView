#pragma once

#include <string>

#include "../IDrawer.h"

class PerformanceGraphGui : public IDrawer
{
public:
	PerformanceGraphGui();

	void Draw() const override;

	static inline std::string GuiName = "Performance Graph";
};