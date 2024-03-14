#pragma once
#include "subsystems.h"

#define ENGINE_SYSTEM_VERSION "Engine001"

abstract_class IEngine : public IAppSystem
{
public:
	virtual ~IEngine() = default;

	virtual bool Setup() = 0;

	virtual int Main() = 0;
	virtual bool GetQuitting() const = 0;
	virtual void SetQuitting(bool quit) = 0;

	virtual float GetFrameTime() const = 0;
};
