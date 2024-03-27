#include "baseentity.h"
#include "render/isprite.h"

CBaseEntity::CBaseEntity()
	: m_pSprite(nullptr)
{
}

void CBaseEntity::Spawn()
{
}

void CBaseEntity::Update(float dt)
{
	m_Transform.position += m_Velocity * dt * 200;
}

void CBaseEntity::Render()
{
}

IRenderable* CBaseEntity::GetRenderable()
{
	return this;
}

bool CBaseEntity::MakeMove(MoveInfo_t& cmd)
{
	m_Velocity = { cmd.sidemove, cmd.forwardmove };

	return true;
}

Transform_t& CBaseEntity::GetTransform()
{
	return m_Transform;
}

void CBaseEntity::SetPos(float x, float y)
{
	m_Transform.position = { x, y };
}

void CBaseEntity::SetScale(float scale)
{
	SetScale(scale, scale);
}

void CBaseEntity::SetScale(float scale_x, float scale_y)
{
	m_Transform.scale = { scale_x, scale_y };
}
