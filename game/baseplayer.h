#pragma once
#include "baseanimated.h"
#include "game/ieventlistener.h"

class CBasePlayer : public CBaseAnimated, IEventListener
{
public:
	CBasePlayer();
	virtual ~CBasePlayer() override;
	
	virtual void Spawn() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	void CheckAnimationEvents() override;

	virtual void FireGameEvent(IEvent* event) override;

	static CBasePlayer* GetLocalPlayer();

private:

};
