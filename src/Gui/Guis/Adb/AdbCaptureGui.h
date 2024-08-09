#pragma once

#include <string>
#include <vector>

#include "../Drawer.h"

class AdbCaptureGui : public Drawer
{
public:
	~AdbCaptureGui() override;

	void Draw() override;
	void ClearLiveLogcatButton();
	std::string& GetName() const override;

	static inline std::string GuiName = "Adb Performance Capture";

private:
	void LiveLogcatOutputView();
	void CaptureLogcatButton();
	void GetDevicesButton();
	char GetLogcatPriority(const std::string& logLine);

	std::string targetApplication;
};
