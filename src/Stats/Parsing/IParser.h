#pragma once

#include <string>

class IParser
{
public:
	virtual ~IParser() = default;
	virtual void Parse(const std::string& logLine) const = 0;
};