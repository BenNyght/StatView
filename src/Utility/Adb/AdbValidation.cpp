
#include "AdbValidation.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "AdbUtility.h"
#include "DeviceInfo.h"

bool AdbValidation::IsAdbInstalled()
{
    try 
    {
        std::string output = AdbUtility::RunCommandToFile("adb version");

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

bool AdbValidation::IsDeviceAvailable()
{
	if (GetConnectedDevices().empty())
	{
		return false;
	}

	return true;
}

std::vector<DeviceInfo> AdbValidation::GetConnectedDevices()
{
    std::vector<DeviceInfo> devices;

    if (IsAdbInstalled() == false)
    {
	    return devices;
    }

	try
    {
		const std::string output = AdbUtility::RunCommandToFile("adb devices");
        std::istringstream iss(output);
        std::string line;
        bool headerSkipped = false;

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