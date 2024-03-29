#include "baseentity.h"
#include "render/isprite.h"

CBaseEntity::CBaseEntity()
	: m_ViewDirection(ViewDirection_t::Down), m_pSprite(nullptr), m_flSpawnTime(0)
{
}

void CBaseEntity::Spawn()
{
	m_flSpawnTime = 0;
}

void CBaseEntity::Update(float dt)
{
	m_flSpawnTime += dt;
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
	m_ViewDirection = cmd.viewdirection;

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
