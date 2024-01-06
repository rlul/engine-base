#include "engine.h"
#include "engine/engine.h"
#include "render/igraphics.h"
#include "core/icommandline.h"
#include <iostream>

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char **argv)
#endif
{
	int result = 0;

#if defined(_WIN32) && defined(_DEBUG)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

#ifdef _WIN32
	CommandLine()->Create(lpCmdLine);
#else
	CommandLine()->Create(argc, argv);
#endif

	if(!Engine()->Setup())
	{
		printf("Failed to setup engine!\n");
		return 0;
	}

	if (!Graphics()->Setup())
	{
		printf("Failed to setup graphics system!\n");
		return 0;
	}

	result = Engine()->Main();
	Graphics()->Shutdown();
	Engine()->Shutdown();

	return result;
}
