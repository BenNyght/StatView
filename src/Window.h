#pragma once

#include <SDL.h>
#include "Update/UpdateHandler.h"

class Window
{
public:
	int Setup();
	int TearDown() const;
	void Update(bool&);

private:
	SDL_Window* window;
	SDL_GLContext gl_context;
};
