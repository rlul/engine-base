#include "engine/module.h"
#include "subsystem/iappsystemgroup.h"
#include "engine/iengine.h"
#include "engine/igameeventmanager.h"
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

	AppSystemGroup()->RegisterSystem(Engine());
	AppSystemGroup()->RegisterSystem(GameEventManager());
	AppSystemGroup()->RegisterSystem(Graphics());

	if (!AppSystemGroup()->SetupSystems())
	{
		return 1;
	}

	result = Engine()->Main();

	AppSystemGroup()->ShutdownSystems();

	return result;
}
