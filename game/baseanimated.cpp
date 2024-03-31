#include "baseanimated.h"
#include "render/isprite.h"
#include "render/ispritesystem.h"
#include "subsystems.h"
#include "common.h"
#include <cstring>
#include <cmath>

CBaseAnimated::CBaseAnimated()
	: m_flAnimationTime(0.f), m_flCycle(0), m_bAnimationPaused(false), m_flPlaybackRate(1.f), m_CurrentAnimation()
{
}

void CBaseAnimated::Spawn()
{
	CBaseEntity::Spawn();

	int width, height;
	m_pSprite->GetFrameSize(width, height);
	m_BoundsMins = { -width / 2, -height / 2 };
	m_BoundsMaxs = { width / 2, height / 2 };
}

void CBaseAnimated::Update(float dt)
{
	CBaseEntity::Update(dt);
}

void CBaseAnimated::Render()
{
	Vector2D_t mins, maxs;
	float scale_x = m_Scale.x, scale_y = m_Scale.y;

	GetWorldBounds(mins, maxs);

	UpdateAnimations();

	g_pSpriteSystem->DrawSpriteEx(m_pSprite, m_CurrentAnimation.id, m_flCycle, mins.x, mins.y, scale_x, scale_y);
}

void CBaseAnimated::SetCurrentAnimation(const char* name)
{
	if (!name || name[0] == '\0' || strcmp(name, m_CurrentAnimation.name) == 0)
		return;

	if (m_pSprite->IsAnimationValid(name))
	{
		m_CurrentAnimation.id = m_pSprite->GetAnimationId(name);
		strcpy_s(m_CurrentAnimation.name, 64, name);
	}
}

float CBaseAnimated::GetPlaybackRate() const
{
	return m_flPlaybackRate;
}

void CBaseAnimated::SetPlaybackRate(float rate)
{
	m_flPlaybackRate = rate;
}

void CBaseAnimated::UpdateAnimations()
{
	FrameAdvance();
}

void CBaseAnimated::PauseAnimation(bool pause)
{
	m_bAnimationPaused = pause;
}

bool CBaseAnimated::IsPaused() const
{
	return m_bAnimationPaused;
}

void CBaseAnimated::ResetAnimation()
{
	m_flCycle = 0.f;
}

float CBaseAnimated::FrameAdvance(float interval)
{
	if (m_bAnimationPaused)
		return 0.f;

	float current_time = COM_GetTime();

	if (interval == 0.f)
	{
		interval = current_time - m_flAnimationTime;
	}

    m_flAnimationTime = current_time;

	if (m_flPlaybackRate == 0.f)
		return 0.f;
	
	int frame_count = m_pSprite->GetFrameCount(m_CurrentAnimation.id);
	float frame_rate = m_pSprite->GetFrameRate(m_CurrentAnimation.id);

	m_flCycle += interval * m_flPlaybackRate * frame_rate;

	if (m_flCycle < 0.f)
	{
		m_flCycle = frame_count - std::fmod(-m_flCycle, frame_count);
	}
	else if (m_flCycle >= frame_count)
	{
		m_flCycle = std::fmod(m_flCycle, frame_count);
	}

	return interval;
}

void CBaseAnimated::CheckAnimationEvents()
{

}

const char* CBaseAnimated::GetCurrentAnimationName() const
{
	return m_CurrentAnimation.name;
}
