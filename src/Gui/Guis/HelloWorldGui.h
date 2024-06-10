#pragma once

#include <string>

#include "../IDrawer.h"

class HelloWorldGui : public IDrawer
{
public:
	void Draw() const override;

	static inline std::string GuiName = "Hello World";
};
