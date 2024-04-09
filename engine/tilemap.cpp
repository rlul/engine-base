#include "tilemap.h"
#include "subsystems.h"
#include "render/itexturesystem.h"
#include <tmxlite/Map.hpp>

#include "tilelayer.h"

CTileMap::CTileMap(std::string_view name)
	: m_Name(name)
{
}

bool CTileMap::Load(const tmx::Map& map)
{
	printf("Loading map: %s\n", m_Name.c_str());

	if (map.getOrientation() != tmx::Orientation::Orthogonal)
	{
		printf("Unsupported orientation for map: %s\n", m_Name.c_str());
		return false;
	}

	switch (map.getRenderOrder())
	{
	case tmx::RenderOrder::RightDown:
		m_RenderOrder = RenderOrder_t::RightDown;
		break;
	case tmx::RenderOrder::RightUp:
		m_RenderOrder = RenderOrder_t::RightUp;
		break;
	case tmx::RenderOrder::LeftDown:
		m_RenderOrder = RenderOrder_t::LeftDown;
		break;
	case tmx::RenderOrder::LeftUp:
		m_RenderOrder = RenderOrder_t::LeftUp;
		break;
	case tmx::RenderOrder::None:
		printf("Render order not set for map: %s\n", m_Name.c_str());
		return false;
	}

	if (!LoadTileSets(map))
	{
		printf("Failed to load tilesets for map: %s\n", m_Name.c_str());
		return false;
	}

	if (!LoadLayers(map))
	{
		printf("Failed to load layers for map: %s\n", m_Name.c_str());
		return false;
	}

	printf("Finished loading map: %s\n", m_Name.c_str());
	return true;
}

void CTileMap::Update(float dt)
{

}

void CTileMap::Render() const
{
	for (const auto& layer : m_pLayers)
	{
		layer->Render();
	}
}

bool CTileMap::LoadTileSets(const tmx::Map& map)
{
	auto tilesets = map.getTilesets();
	for (const auto& tileset_handle : tilesets)
	{
		auto tileset = g_pTextureSystem->LoadTileSet(tileset_handle);
		if (!tileset)
		{
			printf("Failed to load tileset: %s\n", tileset_handle.getName().c_str());
			return false;
		}
		printf("Loaded tileset: %s\n", tileset->GetName().c_str());
		m_pTileSets.push_back(tileset);
	}

	return true;
}

bool CTileMap::LoadLayers(const tmx::Map& map)
{
	const auto& layers = map.getLayers();
	for (const auto& layer_handle : layers)
	{
		if (layer_handle->getType() == tmx::Layer::Type::Tile)
		{
			CTileLayer* layer = new CTileLayer(layer_handle->getName(), m_pTileSets);
			if (!layer->Load(*layer_handle))
			{
				printf("Failed to load layer: %s\n", layer_handle->getName().c_str());
				return false;
			}
			printf("Loaded layer: %s\n", layer->GetName().c_str());
			m_pLayers.push_back(layer);
		}
	}

	return true;
}
