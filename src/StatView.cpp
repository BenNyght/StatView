
#include <SDL.h>
#include "Window.h"

int main(int, char**)
{
    Window window {};
    auto result = window.Setup();
    if (result != 0)
    {
	    return result;
    }

    // Main loop
    bool done = false;
    while (!done)
    {
        window.Update(done);
    }

    result = window.TearDown();
    if (result != 0)
    {
	    return result;
    }

    return 0;
}