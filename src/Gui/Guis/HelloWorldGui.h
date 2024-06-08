#pragma once

#include "../IDrawer.h"

class HelloWorldGui : public IDrawer
{
public:
	void Draw() const override;
};
