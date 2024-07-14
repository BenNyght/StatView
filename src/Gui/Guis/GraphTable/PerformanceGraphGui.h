#pragma once

#include <string>
#include "Gui/Drawer.h"

class PerformanceGraphGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Performance Graph";

private:
	static void DrawGraphControls(bool& showLines, bool& showFills, float& fillRef, int& shadeMode);
};
