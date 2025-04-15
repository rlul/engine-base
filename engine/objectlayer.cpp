#include "objectlayer.h"
#include "subsystems.h"
#include "game/igameclient.h"
#include "game/ientitylist.h"
#include "game/ibaseentity.h"
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <algorithm>

CObjectLayer::CObjectLayer(int ordinal, std::string_view name, Vector2D_t& size)
	: m_iOrdinal(ordinal), m_Name(name), m_flSize(size)
{
}

// inverting y axis because tmxlite uses top-left as origin for some reason
bool CObjectLayer::Load(const tmx::Layer& layer_handle)
{
	auto& objects = layer_handle.getLayerAs<tmx::ObjectGroup>().getObjects();

	for (const auto& object : objects)
	{
		auto pos = object.getPosition();
		pos.y = m_flSize.y - pos.y;

		printf("Object: %s (%f, %f)\n", object.getClass().c_str(), pos.x, pos.y);

		auto entity = g_pGameClient->CreateEntity(object.getClass().c_str());
		if (!entity) continue;

		entity->SetPos(pos.x, pos.y);
		entity->SetLayer(m_iOrdinal);
		g_pEntityList->AddEntity(entity);
	}

	return true;
}

void CObjectLayer::Update(float dt)
{
}

void CObjectLayer::Render() const
{
	std::vector<IBaseEntity*> entities;

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		if (entity->GetLayer() != m_iOrdinal) 
			continue;
		entities.push_back(entity);
	}

	std::ranges::sort(entities, [](const IBaseEntity* first, const IBaseEntity* second) -> bool
		{
			return first->GetPos().y > second->GetPos().y;
		});

	for (const auto& entity : entities) {
		entity->GetRenderable()->Render();
	}
}

std::string CObjectLayer::GetName() const
{
	return m_Name;
}
