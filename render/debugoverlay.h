#pragma once
#include <SDL2/SDL.h>

class CDebugOverlay
{
public:
	CDebugOverlay() = default;
	~CDebugOverlay() = default;

	bool Setup(SDL_Window* window, SDL_Renderer* renderer);
	void Shutdown();

	bool Frame();
	void ProcessEvent(void* sdl_event);

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};

extern CDebugOverlay* g_pDebugOverlay;
