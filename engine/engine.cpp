#include "engine.h"
#include "common.h"
#include <cstdio>
#include <SDL3/SDL.h>

#include "render/igraphics.h"

CEngine g_Engine;
CEngine* Engine()
{
	return &g_Engine;
}

CEngine::CEngine()
	: m_bIsQuitting(false)
{
	
}

CEngine::~CEngine()
{
	
}

bool CEngine::Setup()
{
	printf("Game Path: %s\n", COM_GetGameDir().c_str());

	return true;
}

void CEngine::Shutdown()
{
	
}

int CEngine::Main()
{
	int result = 0;	// stop

	if (!MainLoop())
	{
		result = 1;	// restart
	}

	return result;
}

bool CEngine::MainLoop()
{
	while (true)
	{
		if (GetQuitting())
		{
			return true;
		}
		PollEvent();
		Frame();
	}

	return false;
}

void CEngine::PollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		{
			SetQuitting(true);
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void CEngine::Frame()
{
	Graphics()->Frame();
}

