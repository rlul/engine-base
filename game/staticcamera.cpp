#include "staticcamera.h"
#include "subsystems.h"
#include "engine/iinputsystem.h"
#include "game/ibaseentity.h"
#include "game/ientitylist.h"
#include "render/igraphics.h"
#include <vector>
#include <algorithm>

CStaticCamera::CStaticCamera()
	: m_pRenderView(nullptr)
{
}

CStaticCamera::~CStaticCamera()
{
	delete m_pRenderView;
}

bool CStaticCamera::Setup()
{
	m_pRenderView = new CRenderView;

	return true;
}

void CStaticCamera::Shutdown()
{
	delete m_pRenderView;
	m_pRenderView = nullptr;
}

void CStaticCamera::Update(float dt)
{
	if (g_pInputSystem->IsKeyDown(SDLK_UP))
	{
		SetPos(m_pRenderView->m_Pos + Vector2D_t{ 0, 2 });
	}
	if (g_pInputSystem->IsKeyDown(SDLK_DOWN))
	{
		SetPos(m_pRenderView->m_Pos + Vector2D_t{0, -2});
	}
	if (g_pInputSystem->IsKeyDown(SDLK_LEFT))
	{
		SetPos(m_pRenderView->m_Pos + Vector2D_t{ -2, 0 });
	}
	if (g_pInputSystem->IsKeyDown(SDLK_RIGHT))
	{
		SetPos(m_pRenderView->m_Pos + Vector2D_t{ 2, 0 });
	}

	if (g_pInputSystem->IsKeyDown(SDLK_PAGEUP))
	{
		SetScale(m_pRenderView->m_flScale + 0.03f);
	}
	if (g_pInputSystem->IsKeyDown(SDLK_PAGEDOWN))
	{
		SetScale(m_pRenderView->m_flScale - 0.03f);
	}

	//if (g_pInputSystem->IsKeyDown(SDLK_LEFTBRACKET))
	//{
	//	SetRotation(m_pRenderView->m_flRotation - 1.f);
	//}
	//if (g_pInputSystem->IsKeyDown(SDLK_RIGHTBRACKET))
	//{
	//	SetRotation(m_pRenderView->m_flRotation + 1.f);
	//}
}

void CStaticCamera::Render() const
{
	std::vector<IBaseEntity*> entities;

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
		entities.push_back(g_pEntityList->GetEntity(i));

	std::ranges::sort(entities, [](const IBaseEntity* first, const IBaseEntity* second) -> bool
	{
		return first->GetPos().y > second->GetPos().y;
	});

	for (const auto& entity : entities) {
		entity->GetRenderable()->Render();
	}
}

void CStaticCamera::ScreenToWorld(float x, float y, float& out_x, float& out_y) const
{

}

bool CStaticCamera::WorldToScreen(float x, float y, float& out_x, float& out_y) const
{
	const Vector3D_t world = { x, y, 1.0f};
	const Vector3D_t screen = m_pRenderView->m_ViewMatrix * world;

	out_x = screen.x; out_y = m_pRenderView->m_Size.y - screen.y;
	return IsVisible(out_x, out_y);
}

bool CStaticCamera::IsVisible(float x, float y, float w, float h) const
{
	// TODO: Implement this
	return true;
}

bool CStaticCamera::IsVisible(const IBaseEntity* entity) const
{
	return IsVisible(entity->GetPos(), entity->GetSize());
}

void CStaticCamera::UpdateViewMatrix()
{
	m_pRenderView->UpdateViewMatrix();
}
