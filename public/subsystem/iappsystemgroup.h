#pragma once
#include "subsystem/module.h"

#define GetAppSystem(x) AppSystemGroup()->GetSystem(x)

class IAppSystem;

class IAppSystemGroup
{
public:
	virtual ~IAppSystemGroup() = default;

	virtual bool SetupSystems() = 0;
	virtual void ShutdownSystems() = 0;
	virtual bool RegisterSystem(IAppSystem* subsystem) = 0;
	virtual IAppSystem* GetSystem(const char* name) const = 0;
};

SUBSYSTEM_API IAppSystemGroup* AppSystemGroup();
