#pragma once
#include "baseanimated.h"

class CBaseItem : public CBaseAnimated
{
public:
	CBaseItem() = default;
	virtual ~CBaseItem() override = default;

	virtual void Update(float dt) override;
	virtual void Render() override;

};
