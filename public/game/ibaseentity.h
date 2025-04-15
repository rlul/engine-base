#pragma once
#include "gamemath.h"
#include "irenderable.h"

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

abstract_class IBaseEntity : public IRenderable
{
public:
	virtual ~IBaseEntity() = default;

	virtual void Spawn() = 0;

	virtual void Update(float dt) = 0;

	virtual bool MakeMove(MoveInfo_t& cmd) = 0;

	virtual void GetPos(float& x, float& y) = 0;
	virtual Vector2D_t GetPos() const = 0;
	virtual void GetBounds(Vector2D_t& mins, Vector2D_t& maxs) const = 0;
	virtual void GetWorldBounds(Vector2D_t& mins, Vector2D_t& maxs) const = 0;
	virtual void GetSize(float& width, float& height) const = 0;
	virtual Vector2D_t GetSize() const = 0;
	virtual int GetLayer() const = 0;

	virtual void SetPos(float x, float y) = 0;
	virtual void SetPos(Vector2D_t& pos) = 0;
	virtual void SetSize(float width, float height) = 0;
	virtual void SetSize(Vector2D_t& size) = 0;
	virtual void SetScale(float scale) = 0;
	virtual void SetScale(float scale_x, float scale_y) = 0;
	virtual void SetLayer(int id) = 0;
};
