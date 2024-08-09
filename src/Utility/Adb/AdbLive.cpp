
#include "AdbLive.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "AdbUtility.h"
#include "AdbValidation.h"
#include "PathUtility.h"

std::string AdbLive::GetLiveLogcatPath()
{
	const std::string resources = GetTempFolderPath();
	const std::string file = "LiveLogcat.log";
	return resources + file;
}

bool AdbLive::LiveLogcatExists()
{
    return std::filesystem::exists(GetLiveLogcatPath());
}

void AdbLive::ClearLiveLogcat()
{
    std::ofstream clearFile(GetLiveLogcatPath(), std::ios::trunc);
    clearFile.close();

    if (AdbValidation::IsDeviceAvailable())
    {
	    AdbUtility::RunCommand("adb logcat -c");
    }
}

void AdbLive::LiveLogcat()
{
    if (AdbValidation::IsDeviceAvailable() == false)
    {
	    return;
    }

    try
    {
		const std::string adbCommand = "adb logcat > ";
		const std::string fullCommand = adbCommand + GetLiveLogcatPath();

        std::cout << fullCommand << std::endl;

        AdbUtility::RunCommandOnThread(fullCommand);
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Exception caught while checking running logcat: " << e.what() << std::endl;
    }
}