#pragma once
#include <memory>

class ITexture;

abstract_class ISprite
{
public:
	virtual ~ISprite() = default;

	virtual const char* GetName() const = 0;
	virtual std::shared_ptr<ITexture> GetTexture() const = 0;
	virtual void GetSpriteSize(int& columns, int& rows) const = 0;

	virtual void GetFrameSize(int& width, int& height) const = 0;
	virtual int GetFrameCount(int animation_id) const = 0;
	virtual int GetFrameRate(int animation_id) const = 0;
	virtual int GetFrame(int index, int animation_id) const = 0;

	virtual int GetAnimationId(const char* name) const = 0;
	virtual bool IsAnimationValid(int animation_id) const = 0;
	virtual bool IsAnimationValid(const char* name) const = 0;
};
