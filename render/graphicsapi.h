#pragma once

#include <SDL3/SDL.h>

class CGraphicsAPI
{
public:
	CGraphicsAPI();
	~CGraphicsAPI();

	bool Setup();
	void Shutdown();

};
