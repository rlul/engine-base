#include "render/igraphics.h"
#include "subsystem.h"
#include "subsystems.h"
#include "debugoverlay.h"
#include "render/ispritesystem.h"
#include "game/igameclient.h"
#include "game/ibaseentity.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <algorithm>

#include "game/irenderable.h"

#ifdef _WIN32
#include <Windows.h>
#endif

class CGraphics : public IGraphics
{
public:
	CGraphics() = default;
	~CGraphics() override = default;

	bool Setup() override;
	void Shutdown() override;
	const char* GetSystemName() const override { return GRAPHICS_SYSTEM_VERSION; }

	bool Frame() override;
	void ProcessEvent(void* sdl_event) override;

private:
	virtual void BeginScene();
	virtual void EndScene();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};

CGraphics g_Graphics;
CREATE_SINGLE_SYSTEM(CGraphics, IGraphics, GRAPHICS_SYSTEM_VERSION, g_Graphics);

bool CGraphics::Setup()
{
	int window_width = 1280, window_height = 720;

#ifdef _WIN32
	SetProcessDPIAware();
#endif

	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL_Init failed! (%s)\n", SDL_GetError());
		return false;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("IMG_Init failed! (%s)\n", SDL_GetError());
		return false;
	}

	m_pWindow = SDL_CreateWindow("demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		window_width, window_height, NULL);
	if (m_pWindow == NULL)
	{
		printf("SDL_CreateWindow failed! (%s)\n", SDL_GetError());
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == NULL)
	{
		printf("SDL_CreateRenderer failed! (%s)\n", SDL_GetError());
		return false;
	}

	if (!g_pSpriteSystem->Setup(m_pRenderer))
	{
		printf("Failed while setting up sprite system!\n");
		return false;
	}

	if (!g_pDebugOverlay->Setup(m_pWindow, m_pRenderer))
	{
		printf("Failed while setting up debug overlay!\n");
		return false;
	}

	return true;
}

void CGraphics::Shutdown()
{
	g_pDebugOverlay->Shutdown();
	g_pSpriteSystem->Shutdown();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

bool CGraphics::Frame()
{
	BeginScene();

	g_pGameClient->GetLocalPlayer()->GetRenderable()->Render();

	g_pDebugOverlay->Frame();

	EndScene();

	return true;
}

void CGraphics::ProcessEvent(void* sdl_event)
{
	g_pDebugOverlay->ProcessEvent(sdl_event);
}

void CGraphics::BeginScene()
{
	SDL_SetRenderDrawColor(m_pRenderer, 25, 25, 50, 255);
	SDL_RenderClear(m_pRenderer);
}

void CGraphics::EndScene()
{
	SDL_RenderPresent(m_pRenderer);
}