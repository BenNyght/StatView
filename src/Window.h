#pragma once

#include <SDL.h>

#include "imgui.h"
#include "Gui/GuiDrawer.h"

class Window
{
public:
	int Setup();
	int TearDown() const;
	void Update(bool&) const;

private:
	GuiDrawer guiDrawer;
	SDL_Window* window;
	SDL_GLContext gl_context;
};
