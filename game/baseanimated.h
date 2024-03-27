#pragma once
#include "baseentity.h"

class CBaseAnimated : public CBaseEntity
{
public:
	CBaseAnimated();
	virtual ~CBaseAnimated() override = default;

	virtual void Render() override;

	virtual const char* GetCurrentAnimationName() const;
	virtual void SetCurrentAnimation(const char* name) const;

	virtual float GetPlaybackRate() const;
	virtual void SetPlaybackRate(float rate);

	virtual void UpdateAnimations();
	virtual void PauseAnimation(bool pause);
	virtual bool IsPaused() const;
	virtual void ResetAnimation();
	virtual float FrameAdvance(float interval  = 0.f);

private:
	float m_flAnimationTime, m_flCycle;
	float m_flPlaybackRate;
	bool m_bAnimationPaused;
	char m_pszCurrentAnimation[64];
};
