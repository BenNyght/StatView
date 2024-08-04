#pragma once

#include <string>

#include "../Drawer.h"

class AdbUtilityGui : public Drawer
{
public:
	void Draw() const override;
	std::string& GetName() const override;

	static inline std::string GuiName = "Adb Utility";

private:
	static std::string TargetApplication;
};
