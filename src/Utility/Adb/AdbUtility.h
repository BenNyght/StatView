#pragma once
#include <string>
#include <vector>

#include "DeviceInfo.h"

class AdbUtility
{
public:
	static bool IsAdbSetup();
	static void RestartAdb();
	static std::vector<DeviceInfo> GetConnectedDevices();

	static std::string GetLiveLogcatPath();
	static bool LiveLogcatExists();
	static void ClearLiveLogcat();
	static void LiveLogcat();

private:
	static void RunCommandOnThread(const std::string& command);
	static void RunCommand(const std::string& command);
	static std::string RunCommandToFile(const std::string& command);
	static std::string ReadAndCleanupTempFile(const std::string& tempFileName);
};
