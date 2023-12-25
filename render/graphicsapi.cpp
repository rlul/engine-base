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

	return true;
}

void CGraphicsAPI::Shutdown()
{
	
}

