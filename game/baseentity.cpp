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
	m_Position += m_Velocity * dt * 200;
}

void CBaseEntity::Render()
{
}

bool CBaseEntity::MakeMove(MoveInfo_t& cmd)
{
	m_Velocity = { cmd.sidemove, cmd.forwardmove };
	m_ViewDirection = cmd.viewdirection;

	return true;
}

void CBaseEntity::GetPos(float& x, float& y)
{
	x = m_Position.x; y = m_Position.y;
}

Vector2D_t CBaseEntity::GetPos() const
{
	return m_Position;
}

void CBaseEntity::GetBounds(Vector2D_t& mins, Vector2D_t& maxs) const
{
	mins = m_BoundsMins; maxs = m_BoundsMaxs;
}

void CBaseEntity::GetWorldBounds(Vector2D_t& mins, Vector2D_t& maxs) const
{

}

void CBaseEntity::GetSize(float& width, float& height) const
{
	auto size = GetSize();
	width = size.x; height = size.y;
}

Vector2D_t CBaseEntity::GetSize() const
{
	// calculate from bounds
	return { 0,0 };
}

void CBaseEntity::SetPos(float x, float y)
{
	m_Position = { x, y };
}

void CBaseEntity::SetPos(Vector2D_t& pos)
{
	m_Position = pos;
}

void CBaseEntity::SetSize(float width, float height)
{
	// calculate bounds
}

void CBaseEntity::SetSize(Vector2D_t& size)
{
	SetSize(size.x, size.y);
}

void CBaseEntity::SetScale(float scale)
{
	SetScale(scale, scale);
}

void CBaseEntity::SetScale(float scale_x, float scale_y)
{
	m_Scale = { scale_x, scale_y };
}

bool CBaseEntity::ShouldRender() const
{
	return true;
}

ISprite* CBaseEntity::GetSprite() const
{
	return m_pSprite;
}

void CBaseEntity::GetRenderBounds(Vector2D_t& mins, Vector2D_t& maxs) const
{
	mins = m_BoundsMins; maxs = m_BoundsMaxs;
}

IRenderable* CBaseEntity::GetRenderable()
{
	return this;
}
