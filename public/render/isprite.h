#pragma once
#include <SDL2/SDL.h>

abstract_class ISprite
{
public:
	virtual ~ISprite() = default;

	virtual const char* GetPath() const = 0;
	virtual void GetSpriteSize(int& columns, int& rows) const = 0;
	virtual void GetFrameSize(int& width, int& height) const = 0;
	virtual int GetFrameCount() const = 0;
	virtual float GetFrameRate() const = 0;
	virtual void SetFrameRate(float frame_rate) = 0;
	virtual int GetFrame(int index) const = 0;
	virtual SDL_Texture* GetTexture() const = 0;
	virtual const char* GetCurrentAnimation() const = 0;
	virtual bool SetCurrentAnimation(const char* name) = 0;
};
