#pragma once
#include "game/ibaseentity.h"
#include "game/irenderable.h"
#include "gamemath.h"

class ISprite;

class CBaseEntity : public IBaseEntity
{
public:
	CBaseEntity();
	virtual ~CBaseEntity() override = default;

	virtual void Spawn() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual bool MakeMove(MoveInfo_t& cmd) override;

	virtual void GetPos(float& x, float& y) override;
	virtual Vector2D_t GetPos() const override;
	virtual void GetBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;
	virtual void GetWorldBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;
	virtual void GetSize(float& width, float& height) const override;
	virtual Vector2D_t GetSize() const override;

	virtual void SetPos(float x, float y) override;
	virtual void SetPos(Vector2D_t& pos) override;
	virtual void SetSize(float width, float height) override;
	virtual void SetSize(Vector2D_t& size) override;
	virtual void SetScale(float scale) override;
	virtual void SetScale(float scale_x, float scale_y) override;

	bool ShouldRender() const override;
	ISprite* GetSprite() const override;
	void GetRenderBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;

	IRenderable* GetRenderable() override;

protected:
	// Transform stuff
	Vector2D_t m_Position;
	Vector2D_t m_BoundsMins, m_BoundsMaxs;
	Vector2D_t m_Scale;

	Vector2D_t m_Velocity;
	ViewDirection_t m_ViewDirection;
	ISprite* m_pSprite;
	float m_flSpawnTime;
};
