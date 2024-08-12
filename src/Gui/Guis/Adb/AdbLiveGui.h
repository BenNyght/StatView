#pragma once

#include <string>
#include <vector>

#include "../Drawer.h"

class AdbLiveGui : public Drawer
{
public:
	~AdbLiveGui() override;

	void Draw() override;
	void LiveLogcatButton();
	void ClearLiveLogcatButton();
	std::string& GetName() const override;

	static inline std::string GuiName = "Adb Live";

private:
	void LiveLogcatOutputView();
	void GetDevicesButton();

	std::string targetApplication;
};
