#include "subsystem/iappsystemgroup.h"
#include "subsystem/iappsystem.h"
#include <vector>
#include <cstring>
#include <cstdio>

class CAppSystemGroup : public IAppSystemGroup
{
public:
	bool SetupSystems() override;
	void ShutdownSystems() override;
	bool RegisterSystem(IAppSystem* subsystem) override;
	IAppSystem* GetSystem(const char* name) const override;

private:
	std::vector<IAppSystem*> m_vecAppSystemRegistry;
};

CAppSystemGroup g_AppSystemGroup;
IAppSystemGroup* AppSystemGroup()
{
	return &g_AppSystemGroup;
}

bool CAppSystemGroup::SetupSystems()
{
	for (auto subsystem : m_vecAppSystemRegistry)
	{
		if (!subsystem->IsSetup())
		{
			if (!subsystem->Setup())
			{
				printf("%s initialization failed!.\n", subsystem->GetSystemName());
				return false;
			}
		}
		else
		{
			printf("%s had already been initialized.\n", subsystem->GetSystemName());
			continue;
		}
		printf("%s successfully initialized.\n", subsystem->GetSystemName());
	}
	return true;
}

void CAppSystemGroup::ShutdownSystems()
{
	for (auto subsystem : m_vecAppSystemRegistry)
	{
		if (subsystem->IsSetup())
		{
			subsystem->Shutdown();
		}
		else
		{
			printf("Tried to destroy an uninitialized subsystem %s!\n", subsystem->GetSystemName());
		}
	}
}

bool CAppSystemGroup::RegisterSystem(IAppSystem* subsystem)
{
	if (subsystem == nullptr)
	{
		printf("Tried to register a nullptr subsystem!\n");
		return false;
	}
	m_vecAppSystemRegistry.push_back(subsystem);
	return true;
}

IAppSystem* CAppSystemGroup::GetSystem(const char* name) const
{
	for (auto subsystem : m_vecAppSystemRegistry)
	{
		if (!strcmp(name, subsystem->GetSystemName()))
		{
			return subsystem;
		}
	}
	printf("Tried to retrieve a nonexistent subsystem %s!\n", name);
	return nullptr;
}
