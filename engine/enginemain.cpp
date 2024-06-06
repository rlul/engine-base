#include "subsystems.h"
#include "subsystem.h"
#include "engine/module.h"
#include "engine/iengine.h"
#include "render/igraphics.h"
#include "render/itexturesystem.h"
#include "core/icommandline.h"
#include "core/ifilesystem.h"
#include "engine/iinputsystem.h"
#include "game/igameclient.h"
#include <SDL2/SDL.h>

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char** argv)
#endif
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	//auto file = g_pFileSystem->Open("test.txt", IFileSystem::OPEN_READ_WRITE);
	//unsigned int size = g_pFileSystem->Size(file);
	//char* buffer = new char[size + 1] {0, };
	//g_pFileSystem->Read(file, buffer, size);
	//printf("File %s: %s\n", g_pFileSystem->GetFilePath(file), buffer);
	//g_pFileSystem->Close(file);

	printf("Command Line: %s\n", g_pCommandLine->Get());

	if (g_pCommandLine->HasParam("fps"))
	{
		printf("Found \'fps\' parameter, overriding desired FPS to %d\n", g_pCommandLine->GetParamInt("fps"));
	}

	if (g_pCommandLine->HasParam("width") || g_pCommandLine->HasParam("height"))
	{
		int width = 1280;
		int height = 720;

		SDL_Rect display_bounds;
		SDL_GetDisplayBounds(0, &display_bounds);

		if (g_pCommandLine->HasParam("width"))
		{
			int temp_width = g_pCommandLine->GetParamInt("width");
			if (temp_width > 0 || temp_width < display_bounds.w)
			{
				width = temp_width;
			}
		}

		if (g_pCommandLine->HasParam("height"))
		{
			int temp_height = g_pCommandLine->GetParamInt("height");
			if (temp_height > 0 || temp_height < display_bounds.h)
			{
				height = temp_height;
			}
		}

		printf("Overriding default windows size to %dx%d\n", width, height);
	}

	if (g_pEngine == nullptr || !g_pEngine->Setup())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed while setting up g_pEngine!", nullptr);
		//printf("Failed while setting up g_pEngine!\n");
		return 0;
	}
	if (g_pInputSystem == nullptr || !g_pInputSystem->Setup())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed while setting up g_pInputSystem!", nullptr);
		//printf("Failed while setting up g_pInputSystem!\n");
		return 0;
	}
	if (g_pGraphics == nullptr || !g_pGraphics->Setup())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed while setting up g_pGraphics!", nullptr);
		//printf("Failed while setting up g_pGraphics!\n");
		return 0;
	}
	if (g_pGameClient == nullptr || !g_pGameClient->Setup())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed while setting up g_pGameClient!", nullptr);
		//printf("Failed while setting up g_pGameClient!\n");
		return 0;
	}

	g_pEngine->Main();

	g_pGameClient->Shutdown();
	g_pGraphics->Shutdown();
	g_pInputSystem->Shutdown();
	g_pEngine->Shutdown();

	return 0;
}
