#pragma once
#include "render/module.h"
#include "subsystem/iappsystem.h"

#define GRAPHICS_VERSION "Graphics001"

abstract_class IGraphics : public IAppSystem
{
public:
	virtual bool Frame() = 0;
};

RENDER_API IGraphics* Graphics();
