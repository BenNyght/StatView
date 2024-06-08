#pragma once

#include <memory>
#include <vector>

#include "IDrawer.h"

class GuiDrawer
{
public:
	GuiDrawer();

	void Draw() const;

private:
	std::vector<std::unique_ptr<IDrawer>> drawers;
};
