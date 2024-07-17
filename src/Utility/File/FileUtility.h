#pragma once

#include <string>
#include <vector>
#include <iostream>

class FileUtility
{
public:
	static std::string OpenFilePanel(const std::string& title, const std::string& path, std::vector<std::string> extensions);
};
