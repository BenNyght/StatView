
#include "AdbVrApiCapture.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "AdbUtility.h"
#include "AdbValidation.h"
#include "PathUtility.h"

std::string AdbVrApiCapture::GetLiveLogcatPath()
{
	const std::string resources = GetTempFolderPath();
	const std::string file = "VrApiLogcat.log";
	return resources + file;
}

bool AdbVrApiCapture::VrApiLogcatExists()
{
    return std::filesystem::exists(GetLiveLogcatPath());
}

void AdbVrApiCapture::ClearLogcatBuffer()
{
    if (VrApiLogcatExists())
    {
	    std::ofstream clearFile(GetLiveLogcatPath(), std::ios::trunc);
		clearFile.close();
    }

    if (AdbValidation::IsDeviceAvailable())
    {
	    AdbUtility::RunCommand("adb logcat -c");
    }
}

void AdbVrApiCapture::CaptureLogcat()
{
    if (AdbValidation::IsDeviceAvailable() == false)
    {
	    return;
    }

    try
    {
		const std::string adbCommand = "adb logcat -d -s VrApi > ";
		const std::string fullCommand = adbCommand + GetLiveLogcatPath();

        std::cout << fullCommand << std::endl;

        AdbUtility::RunCommand(fullCommand);
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Exception caught while checking running logcat: " << e.what() << std::endl;
    }
}

void AdbVrApiCapture::SaveVrApiCapture()
{
	// TODO Save Capture
}

void AdbVrApiCapture::SaveVrApiCaptureToLocation()
{
	// TODO Save Capture to Location
}