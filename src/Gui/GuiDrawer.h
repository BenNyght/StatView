#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IDrawer.h"

class GuiDrawer
{
public:
	GuiDrawer();

	void Draw() const;

	static void SetupDockBuilder();

	static inline std::string GuiName = "Main Window";

private:
	std::vector<std::unique_ptr<IDrawer>> drawers;
};
