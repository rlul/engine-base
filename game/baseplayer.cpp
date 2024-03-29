#include "baseplayer.h"
#include "game/ievent.h"
#include "render/ispritesystem.h"

CBasePlayer* g_pLocalPlayer = nullptr;

CBasePlayer::CBasePlayer()
{
	m_pSprite = g_pSpriteSystem->LoadSprite("entity/cavegirl_new");
	SetCurrentAnimation("idle");
	m_Transform.scale = { 4, 4 };
}

CBasePlayer::~CBasePlayer()
{
	if (g_pLocalPlayer == this)
		g_pLocalPlayer = nullptr;
}

void CBasePlayer::Spawn()
{
	CBaseAnimated::Spawn();
	g_pLocalPlayer = this;
}

void CBasePlayer::Update(float dt)
{
	CBaseAnimated::Update(dt);

	if (m_Velocity.IsNull())
	{
		ResetAnimation();
		PauseAnimation(true);
	}
	else
	{
		PauseAnimation(false);

		if (m_Velocity.y < 0)
			SetCurrentAnimation("run_up");
		if (m_Velocity.y > 0)
			SetCurrentAnimation("run_down");
		if (m_Velocity.x < 0)
			SetCurrentAnimation("run_left");
		if (m_Velocity.x > 0)
			SetCurrentAnimation("run_right");
	}
}

void CBasePlayer::Render()
{
	CBaseAnimated::Render();
}

void CBasePlayer::FireGameEvent(IEvent* event)
{
	
}

CBasePlayer* CBasePlayer::GetLocalPlayer()
{
	return g_pLocalPlayer;
}
