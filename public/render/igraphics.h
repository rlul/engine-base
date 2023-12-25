#pragma once
#include "render.h"

abstract_class IGraphics
{
public:
	virtual bool Setup() = 0;
	virtual void Shutdown() = 0;

	virtual bool Frame() = 0;
};

RENDER_API IGraphics* Graphics();
