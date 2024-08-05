#pragma once

#include <deque>
#include <string>

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

	std::string targetApplication;
	int targetLineCount = 250;
	std::deque<std::string> liveLog;
};
