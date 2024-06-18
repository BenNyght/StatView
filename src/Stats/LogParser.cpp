
#include "LogParser.h"
#include <string>
#include <iostream>
#include <fstream>

void LogParser::ParseLatest()
{
	// Create a text string, which is used to output the text file
	std::string myText;

	// Read from the text file
	std::ifstream logFile("VrApi.log");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (logFile, myText)) {
	  // Output the text from the file
	  std::cout << myText;
	}

	// Close the file
	logFile.close();

	std::string command = "echo ";
}
