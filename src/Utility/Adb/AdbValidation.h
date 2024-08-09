#pragma once

#include <vector>

#include "DeviceInfo.h"

class AdbValidation
{
public:
	static bool IsAdbInstalled();
	static bool IsDeviceAvailable();
	static std::vector<DeviceInfo> GetConnectedDevices();
};
