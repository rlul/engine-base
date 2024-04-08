#include "subsystems.h"
#include "engine/iengine.h"
#include "engine/iinputsystem.h"
#include "render/igraphics.h"
#include "render/itexturesystem.h"
#include "core/icommandline.h"
#include "core/ifilesystem.h"
#include "game/igameclient.h"
#include "game/ieventsystem.h"
#include "game/ientitylist.h"

struct SystemInfo_t
{
	void* system;
	const char* name;
};

IEngine* g_pEngine = nullptr;
IInputSystem* g_pInputSystem = nullptr;
IGraphics* g_pGraphics = nullptr;
ITextureSystem* g_pTextureSystem = nullptr;
ICommandLine* g_pCommandLine = nullptr;
IFileSystem* g_pFileSystem = nullptr;
IGameClient* g_pGameClient = nullptr;
IEventSystem* g_pEventSystem = nullptr;
IEntityList* g_pEntityList = nullptr;

SystemInfo_t g_AppSystemList[] =
{
	{ &g_pEngine, ENGINE_SYSTEM_VERSION },
	{ &g_pInputSystem, INPUT_SYSTEM_VERSION },
	{ &g_pGraphics, GRAPHICS_SYSTEM_VERSION },
	{ &g_pTextureSystem, TEXTURE_SYSTEM_VERSION },
	{ &g_pCommandLine, COMMANDLINE_SYSTEM_VERSION },
	{ &g_pFileSystem, FILE_SYSTEM_VERSION },
	{ &g_pGameClient, GAME_CLIENT_VERSION },
	{ &g_pEventSystem, EVENT_SYSTEM_VERSION },
	{ &g_pEntityList, ENTITY_LIST_VERSION }
};

void RegisterSystems(GetSystemFn factory, const char* name, IAppSystem** system)
{
	if (*system)
		return;

	*system = factory(name);
}

void ConnectSystems(GetSystemFn* factory_list, unsigned factory_count)
{
	for (unsigned i = 0; i < factory_count; ++i)
	{
		if (!factory_list[i])
			continue;
		for (const auto& info : g_AppSystemList)
		{
			RegisterSystems(factory_list[i], info.name, (IAppSystem**)info.system);
		}
	}
}
