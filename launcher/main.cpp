#include "engine/module.h"
#include "subsystems.h"
#include "subsystem.h"
#include <SDL3/SDL.h>
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
#if defined(_WIN32) && defined(_DEBUG)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	if (!COM_LoadModule("core"))
	{
		SDL_ShowSimpleMessageBox(0, "Error", "Failed to load core module!\n", 0);
		return 1;
	}

	if (!COM_LoadModule("render"))
	{
		SDL_ShowSimpleMessageBox(0, "Error", "Failed to load render module!\n", 0);
		return 1;
	}

	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

#ifdef _WIN32
	return EngineMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
#else
	return EngineMain(argc, argv);
#endif
}
