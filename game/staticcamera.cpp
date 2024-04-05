#include "staticcamera.h"
#include "subsystems.h"
#include "engine/iinputsystem.h"
#include "game/ibaseentity.h"
#include "game/ientitylist.h"
#include "render/igraphics.h"
#include <vector>
#include <algorithm>

CStaticCamera::CStaticCamera()
	: m_pRenderer(nullptr), m_Viewport(), m_flZoom(1.f), m_flRotation(0.f)
{
}

bool CStaticCamera::Setup(SDL_Renderer* renderer)
{
	if (m_pRenderer)
	{
		return false;
	}
	m_pRenderer = renderer;

	return true;
}

void CStaticCamera::Shutdown()
{
	m_pRenderer = nullptr;
}

void CStaticCamera::Update(float dt)
{
	if (g_pInputSystem->IsKeyDown(SDLK_UP))
	{
		SetPos(m_Pos + Vector2D_t{ 0, 5 });
	}
	if (g_pInputSystem->IsKeyDown(SDLK_DOWN))
	{
		SetPos(m_Pos + Vector2D_t{0, -5});
	}
	if (g_pInputSystem->IsKeyDown(SDLK_LEFT))
	{
		SetPos(m_Pos + Vector2D_t{ -5, 0 });
	}
	if (g_pInputSystem->IsKeyDown(SDLK_RIGHT))
	{
		SetPos(m_Pos + Vector2D_t{ 5, 0 });
	}

	if (g_pInputSystem->IsKeyDown(SDLK_PAGEUP))
	{
		SetZoom(m_flZoom + 0.01f);
	}
	if (g_pInputSystem->IsKeyDown(SDLK_PAGEDOWN))
	{
		SetZoom(m_flZoom - 0.01f);
	}

	if (g_pInputSystem->IsKeyDown(SDLK_LEFTBRACKET))
	{
		SetRotation(m_flRotation - 1.f);
	}
	if (g_pInputSystem->IsKeyDown(SDLK_RIGHTBRACKET))
	{
		SetRotation(m_flRotation + 1.f);
	}
}

void CStaticCamera::Render() const
{
	SDL_RenderSetViewport(m_pRenderer, &m_Viewport);
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
	Vector3D_t size = { GetSize().x, GetSize().y, 0.f };
	Vector3D_t pos = { GetPos().x, GetPos().y, 1.f };
	Vector3D_t world = { x, y, 1.0f};
	world -= pos - size * 0.5f;
	Vector3D_t screen = m_ViewMatrix * world;
	//screen.x -= size.x; screen.y -= size.y;

	out_x = screen.x; out_y = m_Viewport.h - screen.y;
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

void CStaticCamera::GetViewport(float& x, float& y, float& w, float& h) const
{
	x = m_Viewport.x; y = m_Viewport.y;
	w = m_Viewport.w; h = m_Viewport.h;
}


void CStaticCamera::SetViewport(float x, float y, float w, float h)
{
	int screen_width, screen_height;

	if (w == NULL || h == NULL)
	{
		g_pGraphics->GetScreenSize(screen_width, screen_height);
		w = w != NULL ? w : screen_width - x;
		h = h != NULL ? h : screen_height - y;
	}

	m_Viewport = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) };
	UpdateTranslateMatrix();
}

void CStaticCamera::UpdateViewMatrix()
{
	m_ViewMatrix = m_TranslateMatrix * m_RotationMatrix * m_ScaleMatrix;
}

void CStaticCamera::UpdateTranslateMatrix()
{
	m_TranslateMatrix = Matrix3x3_t::Translate({ -m_Pos.x, -m_Pos.y});
	UpdateViewMatrix();
}

void CStaticCamera::UpdateRotationMatrix()
{
	m_RotationMatrix = Matrix3x3_t::Rotate(m_flRotation);
	UpdateViewMatrix();
}

void CStaticCamera::UpdateScaleMatrix()
{
	m_ScaleMatrix = Matrix3x3_t::Scale({ m_flZoom, m_flZoom});
	UpdateViewMatrix();
}
