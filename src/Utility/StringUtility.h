#pragma once

#include <string>
#include <vector>

inline std::vector<std::string> Split(const std::string& search, const std::string& delimiter)
{
    size_t startPosition = 0;
	size_t endPosition;
    const size_t delimiterLength = delimiter.length();

    std::vector<std::string> result;

    while ((endPosition = search.find(delimiter, startPosition)) != std::string::npos) 
	{
        std::string token = search.substr (startPosition, endPosition - startPosition);
        startPosition = endPosition + delimiterLength;
        result.push_back (token);
    }

    result.push_back (search.substr (startPosition));
    return result;
}

inline bool Contains(const std::string& search, const std::vector<std::string>& containsList)
{
	for (const auto& containItem : containsList)
	{
		if (search.find(containItem) != std::string::npos) 
		{
		    return true;
		}
	}

	return false;
}

inline bool Contains(const std::string& search, const std::string& contains)
{
	if (search.find(contains) != std::string::npos) 
	{
	    return true;
	}

	return false;
}

inline std::string GetDateAsString()
{
	time_t rawTime;
	char buffer[80];

    time (&rawTime);
	const struct tm* timeInfo = localtime(&rawTime);

    strftime(buffer,80,"%d-%m-%Y_%H-%M-%S",timeInfo);
    return std::string(buffer);
}
