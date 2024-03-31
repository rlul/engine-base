#include "baseplayer.h"
#include "game/ievent.h"
#include "render/ispritesystem.h"
#include <cstdio>

#include "render/isprite.h"

CBasePlayer* g_pLocalPlayer = nullptr;

CBasePlayer::CBasePlayer()
{
	m_pSprite = g_pSpriteSystem->LoadSprite("entity/cavegirl");
	SetCurrentAnimation("idle");
	SetScale(4);

	if (g_pLocalPlayer == nullptr)
	{
		g_pLocalPlayer = this;
	}
	else
	{
		printf("Warning: tried creating multiple local players!\n");
	}
}

CBasePlayer::~CBasePlayer()
{
	if (g_pLocalPlayer == this)
		g_pLocalPlayer = nullptr;
}

void CBasePlayer::Spawn()
{
	CBaseAnimated::Spawn();
}

void CBasePlayer::Update(float dt)
{
	CBaseAnimated::Update(dt);

	CheckAnimationEvents();
}

void CBasePlayer::Render()
{
	CBaseAnimated::Render();
}

void CBasePlayer::CheckAnimationEvents()
{
	CBaseAnimated::CheckAnimationEvents();

	if (m_Velocity.IsNull())
	{
		ResetAnimation();
		PauseAnimation(true);
	}
	else
	{
		PauseAnimation(false);

		switch (m_ViewDirection)
		{
		case ViewDirection_t::Up:
			SetCurrentAnimation("run_up");
			break;
		case ViewDirection_t::Down:
			SetCurrentAnimation("run_down");
			break;
		case ViewDirection_t::Left:
			SetCurrentAnimation("run_left");
			break;
		case ViewDirection_t::Right:
			SetCurrentAnimation("run_right");
			break;
		}
	}
}

void CBasePlayer::FireGameEvent(IEvent* event)
{
	
}

CBasePlayer* CBasePlayer::GetLocalPlayer()
{
	return g_pLocalPlayer;
}
