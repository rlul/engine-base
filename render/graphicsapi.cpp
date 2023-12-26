#include "graphicsapi.h"

#include <cstdio>

CGraphicsAPI::CGraphicsAPI()
{
	
}

CGraphicsAPI::~CGraphicsAPI()
{
	
}

bool CGraphicsAPI::Setup()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL_Init failed! (%s)\n", SDL_GetError());
		return false;
	}

	// TODO: Get resolution from CommandLine()
	m_pWindow = SDL_CreateWindow("engine-demo", 1280, 720, 0);
	if (m_pWindow == NULL)
	{
		printf("SDL_CreateWindow failed! (%s)\n", SDL_GetError());
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL, 0);
	if (m_pRenderer == NULL)
	{
		printf("SDL_CreateRenderer failed! (%s)\n", SDL_GetError());
		return false;
	}

	return true;
}

void CGraphicsAPI::Shutdown()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

void CGraphicsAPI::BeginScene()
{
}

void CGraphicsAPI::EndScene()
{
}

