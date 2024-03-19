#pragma once

class SDL_Texture;

abstract_class ISprite
{
public:
	virtual ~ISprite() = default;

	virtual const char* GetPath() const = 0;
	virtual SDL_Texture* GetTexture() const = 0;
};
