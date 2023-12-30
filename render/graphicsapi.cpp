#include "graphicsapi.h"
#include "base/icommandline.h"

#include <cstdio>

CGraphicsAPI::CGraphicsAPI()
	: m_pWindow(), m_pRenderer()
{
	
}

CGraphicsAPI::~CGraphicsAPI()
{
	
}

bool CGraphicsAPI::Setup()
{
	int window_width = 1280, window_height = 720;

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL_Init failed! (%s)\n", SDL_GetError());
		return false;
	}


	if (CommandLine()->HasParam("width"))
		window_width = CommandLine()->GetParam<int>("width");
	if (CommandLine()->HasParam("height"))
		window_height = CommandLine()->GetParam<int>("height");

	m_pWindow = SDL_CreateWindow("engine-demo", window_width, window_height, 0);
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

