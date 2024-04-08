#pragma once
#include <SDL2/SDL.h>
#include <string>

abstract_class ITexture
{
public:
	virtual ~ITexture() = default;

	virtual const char* GetName() const = 0;
	virtual SDL_Texture* GetTexture() const = 0;
};
