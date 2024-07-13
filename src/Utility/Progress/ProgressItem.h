#pragma once

#include <string>

class ProgressItem
{
public:
	ProgressItem(std::string name, std::string displayText) : Name(std::move(name)), DisplayText(std::move(displayText)) {}

	std::string Name;
	std::string DisplayText;
};
