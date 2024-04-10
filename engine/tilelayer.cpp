#include "tilelayer.h"
#include "subsystems.h"
#include "render/igraphics.h"
#include "render/itexturesystem.h"
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <cstdio>

CTileLayer::CTileLayer(std::string_view name, TileSetList_t& tile_sets)
	: m_Name(name), m_pTileSets(tile_sets)
{
}

bool CTileLayer::Load(const tmx::Layer& layer_handle)
{
	auto& data = layer_handle.getLayerAs<tmx::TileLayer>().getTiles();
	auto size = layer_handle.getLayerAs<tmx::TileLayer>().getSize();
	auto width = size.x; auto height = size.y;

	m_iTileMap.resize(width);
	for (auto& row : m_iTileMap)
	{
		row.resize(height);
	}
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			const auto& tile = data[y * width + x];
			m_iTileMap[x][y] = tile.ID;
		}
	}

	return true;
}

void CTileLayer::Update(float dt)
{
}

// TODO: next_tile_mins.x = current_tile_maxs.x
void CTileLayer::Render() const
{
	int tile_count = m_iTileMap.size() * m_iTileMap[0].size();

	for (const auto& tileset : m_pTileSets)
	{
		const int tile_width = tileset->GetTileWidth(),
			tile_height = tileset->GetTileHeight();
		const Vector2D_t world_origin_mins = { 0,0 },
			world_origin_maxs = { tile_width, tile_height };
		Vector2D_t screen_origin_mins, screen_origin_maxs;

		g_pGraphics->WorldToScreen(world_origin_mins, screen_origin_mins);
		g_pGraphics->WorldToScreen(world_origin_maxs, screen_origin_maxs);

		const Vector2D_t screen_tile_size = screen_origin_maxs - screen_origin_mins;

		for (int i = 0; i < tile_count; ++i)
		{
			int x, y;

			auto tile = TraverseTileMap(i, x, y);
			if (tile == 0)
				continue;

			Vector2D_t screen_tile_mins = screen_origin_mins + Vector2D_t(
				x * screen_tile_size.x,
				y * screen_tile_size.y
			);

			Vector2D_t screen_tile_maxs = screen_tile_mins + screen_tile_size;
			g_pTextureSystem->DrawTile(tileset, tile, screen_tile_mins.x, screen_tile_mins.y,
				screen_tile_maxs.x, screen_tile_maxs.y);

		}
	}
}

void CTileLayer::Print() const
{
	printf("Layer: %s\n", m_Name.c_str());
	for (const auto& row : m_iTileMap)
	{
				for (const auto& tile : row)
				{
								printf("%d ", tile);
		}
		printf("\n");
	}
}

std::string CTileLayer::GetName() const
{
	return m_Name;
}

Tile_t CTileLayer::TraverseTileMap(int index, int& x, int& y) const
{
	x = index % m_iTileMap.size();
	y = index / m_iTileMap.size();
	return m_iTileMap[x][m_iTileMap.size() - y - 1];
}
