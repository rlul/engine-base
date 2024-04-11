#include "baseentity.h"
#include "render/isprite.h"

CBaseEntity::CBaseEntity()
	: m_iLayerOrdinal(0), m_ViewDirection(ViewDirection_t::Down), m_pSprite(nullptr), m_flSpawnTime(0)
{
}

void CBaseEntity::Spawn()
{
	m_flSpawnTime = 0;
}

void CBaseEntity::Update(float dt)
{
	m_flSpawnTime += dt;
	m_Position += m_Velocity * dt * 50;
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
	mins = { m_BoundsMins.x * m_Scale.x, m_BoundsMins.y * m_Scale.y };
	maxs = { m_BoundsMaxs.x * m_Scale.x, m_BoundsMaxs.y * m_Scale.y };
}

void CBaseEntity::GetWorldBounds(Vector2D_t& mins, Vector2D_t& maxs) const
{
	GetBounds(mins, maxs);
	mins += GetPos();
	maxs += GetPos();
}

void CBaseEntity::GetSize(float& width, float& height) const
{
	auto size = GetSize();
	width = size.x; height = size.y;
}

Vector2D_t CBaseEntity::GetSize() const
{
    return m_BoundsMaxs - m_BoundsMins;
}

int CBaseEntity::GetLayer() const
{
	return m_iLayerOrdinal;
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
	m_BoundsMins = { -width / 2, -height / 2 };
	m_BoundsMaxs = { width / 2, height / 2 };
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

void CBaseEntity::SetLayer(int id)
{
	m_iLayerOrdinal = id;
}

bool CBaseEntity::ShouldRender() const
{
	return true;
}

std::shared_ptr<ISprite> CBaseEntity::GetSprite() const
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

CEntityRegistry* g_pEntityRegistry = nullptr;

CEntityRegistry::CEntityRegistry(const char* name, CreateEntityFn fn)
	: m_pszName(name), m_fnFactory(fn), m_pNext(g_pEntityRegistry)
{
	g_pEntityRegistry = this;
}

CreateEntityFn CEntityRegistry::GetEntityFactory(const char* name)
{
	for (auto reg = g_pEntityRegistry; reg; reg = reg->m_pNext)
	{
		if (strcmp(reg->m_pszName, name) == 0)
			return reg->m_fnFactory;
	}

	return nullptr;
}
