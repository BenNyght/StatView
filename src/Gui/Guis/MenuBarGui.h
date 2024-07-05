#pragma once

#include <string>

#include "../IDrawer.h"

class MenuBarGui : public IDrawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Menu Bar";
};
