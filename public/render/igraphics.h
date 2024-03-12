#pragma once
#include "subsystems.h"

#define GRAPHICS_SYSTEM_VERSION "Graphics001"

abstract_class IGraphics : public IAppSystem
{
public:
	virtual ~IGraphics() = default;

	virtual bool Setup() = 0;

	virtual bool Frame() = 0;
	virtual void ProcessEvent(void* sdl_event) = 0;

};
