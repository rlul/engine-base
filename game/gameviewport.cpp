#include "gameviewport.h"
#include "game/icamera.h"
#include "render/renderview.h"
#include "subsystems.h"
#include "staticcamera.h"
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
	m_Rect = { 0,0, screen_w/1, screen_h/1 };

	m_pCamera = new CStaticCamera;
	m_pCamera->Setup();
	m_pCamera->SetPos(0, 0);
	m_pCamera->SetSize(screen_w, screen_h);
	m_pCamera->SetScale(1.f);

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
