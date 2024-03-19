#pragma once
#include "subsystems.h"

#define SPRITE_SYSTEM_VERSION "SpriteSystem001"

class SDL_Renderer;
class ISprite;

abstract_class ISpriteSystem : public IAppSystem
{
public:
	virtual ~ISpriteSystem() = default;

	virtual bool Setup(SDL_Renderer* renderer) = 0;
	
	virtual ISprite* LoadSprite(const char* filename) = 0;
	virtual void UnloadSprite(ISprite* sprite) = 0;
	virtual bool DrawSprite(ISprite* sprite, int x, int y) = 0;

};
