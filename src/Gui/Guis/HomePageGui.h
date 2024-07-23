#pragma once

#include <string>

#include "../Drawer.h"

class HomePageGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Info";
};
