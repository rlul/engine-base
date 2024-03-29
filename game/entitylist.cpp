#include "entitylist.h"
#include "baseentity.h"
#include "baseplayer.h"
#include "subsystem.h"

CEntityList g_EntityList;
CREATE_SINGLE_SYSTEM( CEntityList, IEntityList, ENTITY_LIST_VERSION, g_EntityList );

bool CEntityList::Setup()
{
	return true;
}

void CEntityList::Shutdown()
{
	Release();
}

void CEntityList::Release()
{
	for (auto entity : m_pBaseEntities)
	{
		delete entity;
	}

	m_pBaseEntities.clear();
}

int CEntityList::AddEntity(IBaseEntity* entity)
{
	m_pBaseEntities.push_back(entity);
	return m_pBaseEntities.size();
}

void CEntityList::RemoveEntity(IBaseEntity* entity)
{
	m_pBaseEntities.remove(entity);
}

void CEntityList::RemoveEntity(int index)
{
	if (index < 0 || index >= m_pBaseEntities.size())
	{
		return;
	}

	auto it = m_pBaseEntities.begin();
	std::advance(it, index);
	m_pBaseEntities.erase(it);
}

IBaseEntity* CEntityList::GetEntity(int index)
{
	return *std::next(m_pBaseEntities.begin(), index);
}

int CEntityList::GetEntityCount()
{
	return m_pBaseEntities.size();
}
