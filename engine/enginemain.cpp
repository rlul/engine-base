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

#ifdef _WIN32
int EngineMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int EngineMain(int argc, char** argv)
#endif
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	auto file = g_pFileSystem->Open("test.txt", "game", IFileSystem::OPEN_READ_WRITE);
	unsigned int size = g_pFileSystem->Size(file);
	char* buffer = new char[size + 1] {0, };
	g_pFileSystem->Read(file, buffer, size);
	printf("File %s: %s\n", g_pFileSystem->GetFilePath(file), buffer);
	g_pFileSystem->Close(file);

	printf("Command Line: %s\n", g_pCommandLine->Get());

	g_pEngine->Setup();
	g_pInputSystem->Setup();
	g_pGraphics->Setup();
	g_pGameClient->Setup();

	g_pEngine->Main();

	g_pGameClient->Shutdown();
	g_pGraphics->Shutdown();
	g_pInputSystem->Shutdown();
	g_pEngine->Shutdown();

	return 0;
}
