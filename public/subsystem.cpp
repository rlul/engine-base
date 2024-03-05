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
			GetSystemFn factory = nullptr;
			IAppSystem* system = nullptr;

			if (!name)
				return nullptr;

			factory = GetModuleFactory("engine");
			if (factory)
				if (system = factory(name))
					return system;

			factory = GetModuleFactory("render");
			if (factory)
				if (system = factory(name))
					return system;

			factory = GetModuleFactory("core");
			if (factory)
				if (system = factory(name))
					return system;

			return nullptr;
		};
}
