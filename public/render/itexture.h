#pragma once
#include <SDL2/SDL.h>
#include <string>

abstract_class ITexture
{
public:
	virtual ~ITexture() = default;

	virtual bool IsValid() const = 0;
	virtual std::string GetName() const = 0;
	virtual operator SDL_Texture*() const = 0;
};
