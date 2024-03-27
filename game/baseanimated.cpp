#include "baseanimated.h"
#include "render/isprite.h"
#include "render/ispritesystem.h"
#include "subsystems.h"
#include "common.h"
#include <cstring>
#include <cmath>

CBaseAnimated::CBaseAnimated()
	: m_flAnimationTime(0.f), m_flCycle(0), m_flPlaybackRate(1.f), m_pszCurrentAnimation{ 0, }
{
}

void CBaseAnimated::Render()
{
	int x = m_Transform.position.x, y = m_Transform.position.y;
	float scale_x = m_Transform.scale.x, scale_y = m_Transform.scale.y;

	UpdateAnimations();

	g_pSpriteSystem->DrawSpriteEx(m_pSprite, m_flCycle, x, y, scale_x, scale_y);
}

void CBaseAnimated::SetCurrentAnimation(const char* name) const
{
	if (!name || name[0] == '\0' || strcmp(name, m_pszCurrentAnimation) == 0)
		return;

	if (m_pSprite->SetCurrentAnimation(name))
	{
		strcpy_s((char*)m_pszCurrentAnimation, 64, name);
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
	
	int frame_count = m_pSprite->GetFrameCount();
	float frame_rate = m_pSprite->GetFrameRate();

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

const char* CBaseAnimated::GetCurrentAnimationName() const
{
	return m_pszCurrentAnimation;
}
