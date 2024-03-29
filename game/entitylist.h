#pragma once
#include "game/ientitylist.h"
#include <list>

class CEntityList : public IEntityList
{
public:
	CEntityList() = default;
	virtual ~CEntityList() override = default;

	virtual bool Setup() override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return ENTITY_LIST_VERSION; }

	virtual void Release() override;

	virtual int AddEntity(IBaseEntity* entity) override;
	virtual void RemoveEntity(IBaseEntity* entity) override;
	virtual void RemoveEntity(int index) override;
	virtual IBaseEntity* GetEntity(int index) override;
	virtual int GetEntityCount() override;

private:
	std::list<IBaseEntity*> m_pBaseEntities;

};
