#include "subsystems.h"
#include "engine/iengine.h"
#include "engine/ieventsystem.h"
#include "render/igraphics.h"
#include "core/icommandline.h"

struct SystemInfo_t
{
	void* system;
	const char* name;
};

IEngine* g_pEngine = nullptr;
IEventSystem* g_pEventSystem = nullptr;
IGraphics* g_pGraphics = nullptr;
ICommandLine* g_pCommandLine = nullptr;

SystemInfo_t g_AppSystemList[] =
{
	{ &g_pEngine, ENGINE_SYSTEM_VERSION },
	{ &g_pEventSystem, EVENT_SYSTEM_VERSION },
	{ &g_pGraphics, GRAPHICS_SYSTEM_VERSION },
	{ &g_pCommandLine, COMMANDLINE_SYSTEM_VERSION }
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
