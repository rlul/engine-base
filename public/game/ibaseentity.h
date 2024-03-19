#pragma once
#include "gamemath.h"

abstract_class IBaseEntity
{
public:
	virtual ~IBaseEntity() = default;

	virtual void Spawn() = 0;
	
	virtual transform_t& GetTransform() = 0;
};
