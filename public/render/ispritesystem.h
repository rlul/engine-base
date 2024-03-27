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
	virtual bool DrawSprite(ISprite* sprite, int x, int y, float scale) = 0;
	virtual bool DrawSpriteEx(ISprite* sprite, int frame_index, int x, int y, float scale_x, float scale_y) = 0;

};
