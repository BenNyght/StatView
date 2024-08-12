#pragma once
#include <string>

class AdbVrApiCapture
{
public:
	static std::string GetPathToSaveLatestCapture();
	static bool VrApiLogcatExists();
	static void ClearLogcatBuffer();
	static void CaptureVrApi();
	static void SaveLatestCaptureToLocation();
};
