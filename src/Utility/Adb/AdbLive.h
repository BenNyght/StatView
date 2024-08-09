#pragma once
#include <string>

class AdbLive
{
public:
	static std::string GetLiveLogcatPath();
	static bool LiveLogcatExists();
	static void ClearLiveLogcat();
	static void LiveLogcat();
};
