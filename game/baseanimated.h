#pragma once
#include "baseentity.h"

class CBaseAnimated : public CBaseEntity
{
	struct AnimationInfo_t
	{
		AnimationInfo_t() : name{ 0, }, id(-1) {}

		char name[64];
		int id;
	};

public:
	CBaseAnimated();
	virtual ~CBaseAnimated() override = default;

	virtual void Spawn() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual const char* GetCurrentAnimationName() const;
	virtual void SetCurrentAnimation(const char* name);

	virtual float GetPlaybackRate() const;
	virtual void SetPlaybackRate(float rate);

	virtual void UpdateAnimations();
	virtual void PauseAnimation(bool pause);
	virtual bool IsPaused() const;
	virtual void ResetAnimation();
	virtual float FrameAdvance(float interval  = 0.f);
	virtual void CheckAnimationEvents();

private:
	float m_flAnimationTime, m_flCycle;
	bool m_bAnimationPaused;
	float m_flPlaybackRate;
	AnimationInfo_t m_CurrentAnimation;
};
