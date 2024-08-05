#pragma once

#include <string>
#include <vector>

#include "../Drawer.h"

class AdbUtilityGui : public Drawer
{
public:
	~AdbUtilityGui() override;

	void Draw() override;
	void LiveLogcatButton();
	void ClearLiveLogcatButton();
	std::string& GetName() const override;

	static inline std::string GuiName = "Adb Utility";

private:
	void ReadLog();
	void LiveLogcatOutputView();
	void GetDevicesButton();
	char GetLogcatPriority(const std::string& logLine);

	std::string targetApplication;
};
