#pragma once
#include "gamemath.h"
#include <memory>

class ISprite;

abstract_class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void Render() = 0;
	virtual bool ShouldRender() const = 0;
	virtual std::shared_ptr<ISprite> GetSprite() const = 0;

	virtual void GetRenderBounds(Vector2D_t& mins, Vector2D_t& maxs) const = 0;


	virtual IRenderable* GetRenderable() = 0;
};
