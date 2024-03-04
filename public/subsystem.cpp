#include "subsystem.h"
#include "common.h"
#include <cstring>

SystemRegistration* g_pSystemsRoot = nullptr;

SystemRegistration::SystemRegistration(CreateSystemFn fn, const char* name)
	: m_fnFactory(fn), m_pszName(name), m_pNext(g_pSystemsRoot)
{
	g_pSystemsRoot = this;
}

IAppSystem* GetSystem(const char* name)
{
	for (auto subsystem = g_pSystemsRoot; subsystem; subsystem = subsystem->m_pNext)
	{
		if (!strcmp(name, subsystem->m_pszName))
			return subsystem->m_fnFactory();
	}

	return nullptr;
}

GetSystemFn GetModuleFactory(const char* module_name)
{
	if (!module_name)
		return nullptr;

	void* module = COM_LoadModule(module_name);
	if (!module)
		return nullptr;

	return (GetSystemFn)COM_LoadSymbol(module, "GetSystem");
}

GetSystemFn GetGameFactory()
{
	return [](const char* name) -> IAppSystem*
		{
			if (!name)
				return nullptr;

			auto engine_factory = GetModuleFactory("engine");
			if (engine_factory)
			{
				auto system = engine_factory(name);
				if (system)
					return system;
			}

			auto render_factory = GetModuleFactory("render");
			if (render_factory)
			{
				auto system = render_factory(name);
				if (system)
					return system;
			}

			auto core_factory = GetModuleFactory("core");
			if (core_factory)
			{
				auto system = core_factory(name);
				if (system)
					return system;
			}

			return nullptr;
		};
}
