#pragma once
#include "game/ibaseentity.h"
#include "game/irenderable.h"
#include "gamemath.h"

class ISprite;

class CBaseEntity : public IBaseEntity, IRenderable
{
public:
	CBaseEntity();
	virtual ~CBaseEntity() override = default;

	virtual void Spawn() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual IRenderable* GetRenderable() override;

	virtual bool MakeMove(MoveInfo_t& cmd) override;

	virtual Transform_t& GetTransform() override;
	virtual void SetPos(float x, float y) override;
	virtual void SetScale(float scale) override;
	virtual void SetScale(float scale_x, float scale_y) override;

protected:
	Transform_t m_Transform;
	Vector2D_t m_Velocity;
	ViewDirection_t m_ViewDirection;
	ISprite* m_pSprite;
	float m_flSpawnTime;
};
