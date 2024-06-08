#ifndef STATVIEW_H
#define STATVIEW_H

#include <SDL.h>

bool InitSDL(SDL_Window*& window, SDL_GLContext& gl_context);
bool InitGLEW();

void SetupImGui();
void StartImGuiFrame();
void RenderImGuiFrame(SDL_Window* window);

#endif // STATVIEW_H
