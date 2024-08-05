#pragma once

#include <string>

#include "../Drawer.h"

class HelloWorldGui : public Drawer
{
public:
	void Draw() override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Hello World";
};
