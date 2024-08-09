#pragma once
#include <string>

class AdbVrApiCapture
{
public:
	static std::string GetLiveLogcatPath();
	static bool VrApiLogcatExists();
	static void ClearLogcatBuffer();
	static void CaptureLogcat();
	static void SaveVrApiCapture();
	static void SaveVrApiCaptureToLocation();
};
