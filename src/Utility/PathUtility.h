#pragma once
#include <filesystem>
#include <string>

inline std::string GetCaptureFolderPath()
{
	std::string currentPath = std::filesystem::current_path().string();
	std::string fullPath = currentPath + "\\captures\\";
	if (std::filesystem::exists(fullPath) == false)
	{
		std::filesystem::create_directory(fullPath);
	}
	return fullPath;
}

inline std::string GetLatestCaptureFile()
{
    std::string captureFolderPath = GetCaptureFolderPath();
    std::filesystem::path latestFilePath;
    bool found = false;

    for (const auto& entry : std::filesystem::directory_iterator(captureFolderPath))
    {
        if (entry.is_regular_file() && (found == false || entry.path() > latestFilePath))
        {
            latestFilePath = entry.path();
            found = true;
        }
    }

    if (found == false)
    {
	    return "";
    }
    return latestFilePath.string();
}

inline std::string GetResourcesFolderPath()
{
	std::string currentPath = std::filesystem::current_path().string();
	std::string fullPath = currentPath + "\\resources\\";
	if (std::filesystem::exists(fullPath) == false)
	{
		std::filesystem::create_directory(fullPath);
	}
	return fullPath;
}

inline std::string GetTempFolderPath()
{
	std::string currentPath = std::filesystem::current_path().string();
	std::string fullPath = currentPath + "\\temp\\";
	if (std::filesystem::exists(fullPath) == false)
	{
		std::filesystem::create_directory(fullPath);
	}
	return fullPath;
}