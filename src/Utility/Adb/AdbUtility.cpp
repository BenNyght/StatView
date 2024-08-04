
#include "AdbUtility.h"

#include <cstdio>
#include <iostream>
#include <array>
#include <fstream>
#include <sstream>

std::vector<DeviceInfo> AdbUtility::GetConnectedDevices()
{
    std::vector<DeviceInfo> devices;
	try 
    {
		const std::string output = RunCommand("adb devices");
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

std::string AdbUtility::RunCommand(const std::string& command)
{
    const std::string tempFileName = "temp_command_output.txt";
    const std::string fullCommand = command + " > " + tempFileName + " 2>&1"; // Redirect stderr to stdout

    // Execute the command and redirect output to a temporary file
    int systemResult = std::system(fullCommand.c_str());
    if (systemResult != 0) 
    {
        std::cerr << "Command failed with status " << systemResult << ". Command: " << command << std::endl;
    }

    // Open the temporary file to read the output
    std::ifstream inputFile(tempFileName);
    if (!inputFile.is_open()) 
    {
        throw std::runtime_error("Failed to open the temporary file.");
    }

    // Read the output from the file
    std::string output, line;
    while (getline(inputFile, line)) 
    {
        output += line + "\n";
    }

    inputFile.close();
    int removeResult = std::remove(tempFileName.c_str()); // Clean up the temporary file
    if (systemResult != 0) 
    {
        std::cerr << "Failed to remove temp output file with status " << systemResult << ". Command: " << command << std::endl;
    }

    return output;
}


//  const std::string adbCommand = "adb logcat -d -s VrApi > ";
//  std::string file = "VrApi.log";
//  std::string fullPath = (std::filesystem::current_path() / file).string();
//  const std::string fullCommand = adbCommand + fullPath;
//  system(("echo " + fullCommand).c_str());
//  system(fullCommand.c_str());