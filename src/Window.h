#pragma once

#include <SDL.h>

#include "imgui.h"
#include "Gui/GuiDrawer.h"

class Window
{
public:
	int Setup();
	int TearDown() const;
	void Update(bool&);

private:
	std::shared_ptr<GuiDrawer> guiDrawer = std::make_shared<GuiDrawer>();
	SDL_Window* window;
	SDL_GLContext gl_context;
};
