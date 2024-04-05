#pragma once
#include <SDL2/SDL.h>

class CDebugOverlay
{
public:
	CDebugOverlay();
	virtual ~CDebugOverlay();

	virtual bool Setup(SDL_Window* window, SDL_Renderer* renderer);
	virtual void Shutdown();

	virtual bool Frame();
	virtual void ProcessEvent(void* sdl_event);

	virtual bool ShouldDraw();

private:
	virtual float CalculateFPS();
	virtual void DrawEntityPos();
	virtual void DrawEntityBounds();
	virtual void DrawWorldOrigin();

private:
	bool m_bShouldDraw;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};

extern CDebugOverlay* g_pDebugOverlay;
