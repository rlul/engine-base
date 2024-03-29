#pragma once
#include "subsystems.h"
#include "ibaseentity.h"

#define ENTITY_LIST_VERSION "EntityList001"

abstract_class IEntityList : public IAppSystem
{
public:
	virtual ~IEntityList() = default;

	virtual bool Setup() = 0;

	virtual void Release() = 0;

	virtual int AddEntity(IBaseEntity* entity) = 0;
	virtual void RemoveEntity(IBaseEntity* entity) = 0;
	virtual void RemoveEntity(int index) = 0;
	virtual IBaseEntity* GetEntity(int index) = 0;
	virtual int GetEntityCount() = 0;
};
