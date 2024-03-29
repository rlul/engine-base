#pragma once
#include <SDL2/SDL.h>

abstract_class ISprite
{
public:
	virtual ~ISprite() = default;

	virtual const char* GetPath() const = 0;
	virtual SDL_Texture* GetTexture() const = 0;

	virtual void GetSpriteSize(int& columns, int& rows) const = 0;
	virtual void GetFrameSize(int& width, int& height) const = 0;

	virtual int GetFrameCount(int animation_id) const = 0;
	virtual float GetFrameRate(int animation_id) const = 0;
	virtual int GetFrame(int index, int animation_id) const = 0;

	virtual int GetAnimationId(const char* animation_name) const = 0;
	virtual bool IsAnimationValid(const char* animation_name) const = 0;
	virtual bool IsAnimationValid(int animation_id) const = 0;
};
