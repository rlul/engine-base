#pragma once
#include "engine/module.h"
#include "subsystem/iappsystem.h"

#define ENGINE_VERSION "Engine001"

abstract_class IEngine : public IAppSystem
{
public:
	virtual int Main() = 0;
	virtual bool GetQuitting() const = 0;
	virtual void SetQuitting(bool quit) = 0;
};

ENGINE_API IEngine* Engine();
