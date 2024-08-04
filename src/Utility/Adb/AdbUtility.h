#pragma once
#include <string>
#include <vector>

#include "DeviceInfo.h"

class AdbUtility
{
public:
	static std::vector<DeviceInfo> GetConnectedDevices();

private:
	static std::string RunCommand(const std::string& command);
};
