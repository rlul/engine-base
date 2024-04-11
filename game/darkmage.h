#pragma once
#include "baseanimated.h"

class CDarkMage : public CBaseAnimated
{
public:
	CDarkMage();
	virtual ~CDarkMage() override;

	virtual void Spawn() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void CheckAnimationEvents() override;

private:
	int m_iWalkDirection;
};
