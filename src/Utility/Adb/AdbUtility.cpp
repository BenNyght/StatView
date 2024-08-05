
#include "AdbUtility.h"

#include <cstdio>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>

#include "PathUtility.h"

bool AdbUtility::IsAdbSetup()
{
    try 
    {
        std::string output = RunCommandToFile("adb version");

        // Check the output for the expected ADB version string
        if (output.find("Android Debug Bridge version") != std::string::npos) 
        {
            return true;
        }
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Exception caught while checking ADB setup: " << e.what() << std::endl;
    }

    return false;
}

void AdbUtility::RestartAdb()
{
    RunCommand("adb kill-server");
    RunCommand("adb start-server");
}

std::string AdbUtility::GetLiveLogcatPath()
{
	std::string resources = GetTempFolderPath();
	std::string file = "VrApiLogcat.log";
	return resources + file;
}

bool AdbUtility::LiveLogcatExists()
{
    return std::filesystem::exists(GetLiveLogcatPath());
}

void AdbUtility::ClearLiveLogcat()
{
    RunCommand("adb logcat -c");
    std::ofstream clearFile(GetLiveLogcatPath(), std::ios::trunc);
    clearFile.close();
}

void AdbUtility::LiveLogcat()
{
    try
    {
		const std::string adbCommand = "adb logcat > ";
		const std::string fullCommand = adbCommand + GetLiveLogcatPath();

        std::cout << fullCommand << std::endl;

        RunCommandOnThread(fullCommand);
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Exception caught while checking running logcat: " << e.what() << std::endl;
    }
}

std::vector<DeviceInfo> AdbUtility::GetConnectedDevices()
{
    std::vector<DeviceInfo> devices;
	try 
    {
		const std::string output = RunCommandToFile("adb devices");
        std::istringstream iss(output);
        std::string line;
        bool headerSkipped = false;

        // Read the output line by line and process each device
        while (std::getline(iss, line))
        {
            if (!headerSkipped)
            {
                headerSkipped = true;
                continue;
            }

            if (line.empty())
            {
                continue;
            }

            std::size_t tabPosition = line.find('\t');
            if (tabPosition != std::string::npos) 
            {
                DeviceInfo device;
                device.id = line.substr(0, tabPosition);
                device.status = line.substr(tabPosition + 1);
                devices.push_back(device);
            }
        }
    }
	catch (const std::exception& e) 
    {
        std::cerr << "Error retrieving connected devices: " << e.what() << std::endl;
    }

    return devices;
}

void AdbUtility::RunCommandOnThread(const std::string& command)
{
    std::thread adbThread(RunCommand, command);
	adbThread.detach();
}

void AdbUtility::RunCommand(const std::string& command)
{
    std::cout << command << std::endl;
	system(command.c_str());
}

std::string AdbUtility::RunCommandToFile(const std::string& command)
{
    const std::string tempFileName = "temp_command_output.txt";
    const std::string fullCommand = command + " > " + tempFileName + " 2>&1"; // Redirect stderr to stdout

    // Execute the command and redirect output to a temporary file
    int systemResult = std::system(fullCommand.c_str());
    if (systemResult != 0) 
    {
        std::cerr << "Command failed with status " << systemResult << ". Command: " << command << std::endl;
    }

    // Read the output from the temporary file and clean it up
    return ReadAndCleanupTempFile(tempFileName);
}

std::string AdbUtility::ReadAndCleanupTempFile(const std::string& tempFileName)
{
    std::ifstream inputFile(tempFileName);
    if (!inputFile.is_open()) 
    {
        throw std::runtime_error("Failed to open the temporary file.");
    }

    std::string output;
	std::string line;
    while (getline(inputFile, line)) 
    {
        output += line + "\n";
    }

    inputFile.close();
    int removeResult = std::remove(tempFileName.c_str()); // Clean up the temporary file
    if (removeResult != 0) 
    {
        std::cerr << "Failed to remove temp output file. Temp file: " << tempFileName << std::endl;
    }

    return output;
}


//  const std::string adbCommand = "adb logcat -d -s VrApi > ";
//  std::string file = "VrApi.log";
//  std::string fullPath = (std::filesystem::current_path() / file).string();
//  const std::string fullCommand = adbCommand + fullPath;
//  system(("echo " + fullCommand).c_str());
//  system(fullCommand.c_str());