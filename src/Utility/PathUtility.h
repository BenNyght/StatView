#pragma once
#include <filesystem>
#include <string>

inline std::string GetResourcesFolderPath()
{
	std::string currentPath = std::filesystem::current_path().string();
	std::string fullPath = currentPath + "/resources/";
	if (std::filesystem::exists(fullPath) == false)
	{
		std::filesystem::create_directory(fullPath);
	}
	return fullPath;
}

inline std::string GetTempFolderPath()
{
	std::string currentPath = std::filesystem::current_path().string();
	std::string fullPath = currentPath + "/temp/";
	if (std::filesystem::exists(fullPath) == false)
	{
		std::filesystem::create_directory(fullPath);
	}
	return fullPath;
}