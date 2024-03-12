#pragma once
#include <SDL3/SDL.h>

class CDebugOverlay
{
public:
	CDebugOverlay() = default;
	~CDebugOverlay() = default;

	bool Setup(SDL_Window* window, SDL_GLContext gl_context);

	bool Frame();
	void ProcessEvent(void* sdl_event);

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_OpenGLContext;
};

extern CDebugOverlay* g_pDebugOverlay;
