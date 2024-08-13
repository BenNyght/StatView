#pragma once

#include <string>

#include "Timer.h"
#include "../Drawer.h"

class AdbCaptureGui : public Drawer
{
public:
	void Draw() override;
	
	std::string& GetName() const override;

	static inline std::string GuiName = "Capture";
};
