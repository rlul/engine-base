#include "gameviewport.h"
#include "game/icamera.h"
#include "subsystems.h"
#include "staticcamera.h"
#include "followcamera.h"
#include "render/igraphics.h"

CGameViewport::CGameViewport()
	: m_pRenderer(nullptr), m_Rect(), m_pCamera(nullptr)
{
}

CGameViewport::~CGameViewport()
{
	delete m_pCamera;
}

bool CGameViewport::Setup(SDL_Renderer* renderer)
{
	int screen_w, screen_h;

	m_pRenderer = renderer;

	g_pGraphics->GetScreenSize(screen_w, screen_h);
	//m_Rect = { 200,200, screen_w/2, screen_h/2 };
	m_Rect = { 0,0, screen_w, screen_h };

	auto camera = new CFollowCamera;
	camera->Setup();
	camera->SetPos(0, 0);
	camera->SetSize(m_Rect.w, m_Rect.h);
	camera->SetScale(1.f);

	m_pCamera = camera;

	return true;
}

void CGameViewport::Shutdown()
{
	m_pCamera->Shutdown();
	delete m_pCamera;
	m_pCamera = nullptr;
}

void CGameViewport::Update(float dt)
{
	m_pCamera->Update(dt);
}

void CGameViewport::Render() const
{
	SDL_RenderSetViewport(m_pRenderer, &m_Rect);
	m_pCamera->Render();
}
