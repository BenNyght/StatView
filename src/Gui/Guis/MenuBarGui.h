#pragma once

#include <string>

#include "../Drawer.h"

class MenuBarGui : public Drawer
{
public:
	void Draw() override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Menu Bar";
};
