#pragma once

#include <string>
#include <vector>

#include "Timer.h"
#include "../Drawer.h"

class AdbCaptureGui : public Drawer
{
public:
	void Draw() override;
	
	std::string& GetName() const override;

	static inline std::string GuiName = "Adb Performance Capture";
};
