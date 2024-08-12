
#include "AdbVrApiCapture.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "AdbUtility.h"
#include "AdbValidation.h"
#include "PathUtility.h"
#include "StringUtility.h"

std::string AdbVrApiCapture::GetPathToSaveLatestCapture()
{
	const std::string resources = GetCaptureFolderPath();
	const std::string fileName = "VrApiLogcat_";
	const std::string dateTime = GetDateAsString();
    const std::string fileExtension = ".log";
	return resources + fileName + dateTime + fileExtension;
}

bool AdbVrApiCapture::VrApiLogcatExists()
{
    return std::filesystem::exists(GetPathToSaveLatestCapture());
}

void AdbVrApiCapture::ClearLogcatBuffer()
{
    if (VrApiLogcatExists())
    {
	    std::ofstream clearFile(GetPathToSaveLatestCapture(), std::ios::trunc);
		clearFile.close();
    }

    if (AdbValidation::IsDeviceAvailable())
    {
	    AdbUtility::RunCommand("adb logcat -c");
    }
}

void AdbVrApiCapture::CaptureVrApi()
{
    if (AdbValidation::IsDeviceAvailable() == false)
    {
	    return;
    }

    try
    {
		const std::string adbCommand = "adb logcat -d -s VrApi > ";
		const std::string fullCommand = adbCommand + GetPathToSaveLatestCapture();
        AdbUtility::RunCommand(fullCommand);
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Exception caught while checking running logcat: " << e.what() << std::endl;
    }
}