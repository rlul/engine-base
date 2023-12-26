#include "engine/engine.h"
#include "render/igraphics.h"
#include "base/icommandline.h"

#include <iostream>
#include <SDL3/SDL.h>

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char **argv)
#endif
{
#if defined(_WIN32) && defined(_DEBUG)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

#ifdef _WIN32
	CommandLine()->Create(lpCmdLine);
#else
	CommandLine()->Create(argc, argv);
#endif

	printf("raw params: %s\n", CommandLine()->Get());
	printf("game path: %s\n", CommandLine()->GetParam("game"));

	if (!Graphics()->Setup())
	{
		printf("Failed to setup graphics system!\n");
		return 0;
	}

	SDL_Event event;
	bool running = true;
	while (SDL_PollEvent(&event) || running)
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			running = false;
		}
	}

	return 0;
}

