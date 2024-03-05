#include "subsystems.h"
#include "subsystem.h"
#include "engine/module.h"
#include "engine/iengine.h"
#include "render/igraphics.h"
#include "core/icommandline.h"
#include "core/ifilesystem.h"

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char** argv)
#endif
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	printf("Command Line: %s\n", g_pCommandLine->Get());

	g_pEngine->Setup();
	g_pGraphics->Setup();

	g_pEngine->Main();

	g_pGraphics->Shutdown();
	g_pEngine->Shutdown();

	return 0;
}
