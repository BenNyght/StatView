#pragma once

#include <string>

#include "../IDrawer.h"

class StatsGui : public IDrawer
{
public:
	void Draw() const override;

	static inline std::string GuiName = "Stats";

private:
	static void PushStyleCompact();
};
