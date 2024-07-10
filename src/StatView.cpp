
#include <filesystem>
#include <SDL.h>
#include "Window.h"
#include "Parsing/LogParser.h"

int main(int, char**)
{
    Window window {};
    auto result = window.Setup();
    if (result != 0)
    {
	    return result;
    }

    LogParser parser { };
    LogParser::ProcessLatest();

 //   const std::string adbCommand = "adb logcat -d -s VrApi > ";
 //   std::string file = "VrApi.log";
	//std::string fullPath = (std::filesystem::current_path() / file).string();
 //   const std::string fullCommand = adbCommand + fullPath;
 //   system(("echo " + fullCommand).c_str());
 //   system(fullCommand.c_str());

    // Main loop
    bool done = false;
    while (!done)
    {
        LogParser::Process(300);
        window.Update(done);
    }

    result = window.TearDown();
    if (result != 0)
    {
	    return result;
    }

    return 0;
}
