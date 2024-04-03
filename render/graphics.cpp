#include "render/igraphics.h"
#include "subsystem.h"
#include "subsystems.h"
#include "debugoverlay.h"
#include "render/ispritesystem.h"
#include "game/igameclient.h"
#include "game/icamera.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <algorithm>
#ifdef _WIN32
#include <Windows.h>
#endif

class CGraphics : public IGraphics
{
public:
	CGraphics() = default;
	virtual ~CGraphics() override = default;

	virtual bool Setup() override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return GRAPHICS_SYSTEM_VERSION; }

	virtual bool Frame() override;
	virtual void ProcessEvent(void* sdl_event) override;

	virtual void ScreenToWorld(float x, float y, float& out_x, float& out_y) const override;
	virtual inline void ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const override;
	virtual bool WorldToScreen(float x, float y, float& out_x, float& out_y) const override;
	virtual inline bool WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const override;

	virtual SDL_Window* GetWindow() const { return m_pWindow; }
	virtual SDL_Renderer* GetRenderer() const { return m_pRenderer; }
	virtual void GetScreenSize(int& w, int& h) const { w = m_iScreenWidth; h = m_iScreenHeight; }

private:
	virtual void BeginScene();
	virtual void EndScene();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_iScreenWidth, m_iScreenHeight;
};

CGraphics g_Graphics;
CREATE_SINGLE_SYSTEM(CGraphics, IGraphics, GRAPHICS_SYSTEM_VERSION, g_Graphics);

bool CGraphics::Setup()
{
	m_iScreenWidth = 1280; m_iScreenHeight = 720;

	if (m_pWindow || m_pRenderer)
	{
		return false;
	}

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
		m_iScreenWidth, m_iScreenHeight, NULL);
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

	g_pGameClient->Render();

	g_pDebugOverlay->Frame();

	EndScene();

	return true;
}

void CGraphics::ProcessEvent(void* sdl_event)
{
	g_pDebugOverlay->ProcessEvent(sdl_event);
}

void CGraphics::ScreenToWorld(float x, float y, float& out_x, float& out_y) const
{
}

void CGraphics::ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const
{
	ScreenToWorld(screen.x, screen.y, world.x, world.y);
}

bool CGraphics::WorldToScreen(float x, float y, float& out_x, float& out_y) const
{
	return g_pGameClient->GetActiveCamera()->WorldToScreen(x, y, out_x, out_y);
}

bool CGraphics::WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const
{
	return WorldToScreen(world.x, world.y, screen.x, screen.y);
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