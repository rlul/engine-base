#pragma once
#include "gamemath.h"

enum class ViewDirection_t
{
	Up,
	Down,
	Left,
	Right
};

struct MoveInfo_t
{
	float forwardmove;
	float sidemove;
    float rotation;
	ViewDirection_t viewdirection;
};

class IRenderable;

abstract_class IBaseEntity
{
public:
	virtual ~IBaseEntity() = default;

	virtual void Spawn() = 0;

	virtual void Update(float dt) = 0;

	virtual IRenderable* GetRenderable() = 0;

	virtual bool MakeMove(MoveInfo_t& cmd) = 0;

	virtual Transform_t& GetTransform() = 0;
	virtual void SetPos(float x, float y) = 0;
	virtual void SetScale(float scale) = 0;
	virtual void SetScale(float scale_x, float scale_y) = 0;
};
