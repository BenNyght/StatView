#pragma once

#include <string>

#include "../Drawer.h"

class MenuBarGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Menu Bar";
};
