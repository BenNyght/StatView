
#include "AdbUtility.h"

#include <cstdio>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>

#include "AdbValidation.h"

void AdbUtility::StartAdb()
{
    if (AdbValidation::IsAdbInstalled())
    {
	    RunCommand("adb start-server");
    }
}

void AdbUtility::RestartAdb()
{
    if (AdbValidation::IsAdbInstalled())
    {
	    RunCommand("adb kill-server");
		RunCommand("adb start-server");
    }
}

void AdbUtility::KillAdb()
{
    if (AdbValidation::IsAdbInstalled())
    {
	    RunCommand("adb kill-server");
    }
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