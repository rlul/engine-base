#pragma once
#include "game/ibaseentity.h"
#include "game/irenderable.h"
#include "math.h"

class CBaseEntity : public IBaseEntity, IRenderable
{
public:
	CBaseEntity() = default;
	~CBaseEntity() override = default;

	void Spawn() override;
	void Render() override;

	transform_t& GetTransform();

protected:
	transform_t m_Transform;
};
