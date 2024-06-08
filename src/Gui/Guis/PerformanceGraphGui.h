#pragma once

#include "../IDrawer.h"

class PerformanceGraphGui : public IDrawer
{
public:
	PerformanceGraphGui();

	void Draw() const override;
};