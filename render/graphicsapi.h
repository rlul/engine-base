#pragma once

#include <SDL3/SDL.h>

class CGraphicsAPI
{
public:
	CGraphicsAPI();
	~CGraphicsAPI();

	bool Setup();
	void Shutdown();

	void BeginScene();
	void EndScene();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};
