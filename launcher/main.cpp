#include "engine/module.h"
#include "core/icommandline.h"
#include "subsystems.h"
#include "subsystem.h"
#include "common.h"
#include <SDL3/SDL.h>
#include <cstdio>

#include "core/ifilesystem.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef _DEBUG
extern "C" {
	DLL_EXPORT int NvOptimusEnablement = 1;
	DLL_EXPORT int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

#ifdef _WIN32
	g_pCommandLine->Create(lpCmdLine);
#else
	g_pCommandLine->Create(argc, argv);
#endif

#ifdef _WIN32
	if (g_pCommandLine->HasParam("dev"))
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}
#endif

	char game_dir[MAX_PATH];
	if (!COM_GetGameDir(game_dir))
	{
		return 1;
	}
	g_pFileSystem->Setup(game_dir);
	printf("Game Directory: %s\n", game_dir);

#ifdef _WIN32
	return EngineMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
#else
	return EngineMain(argc, argv);
#endif
}
