#include "tilelayer.h"
#include "subsystems.h"
#include "render/itileset.h"
#include "render/itexturesystem.h"
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SDL2/SDL.h>
#include <cstdio>

#include "render/igraphics.h"

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

void CTileLayer::Render() const
{
	for (int row = 0; row < m_iTileMap.size(); ++row)
	{
		for (int cols = 0; cols < m_iTileMap[row].size(); ++cols)
		{
			auto tile = m_iTileMap[row][m_iTileMap[row].size() - 1 - cols];
			if (tile == 0)
			{
				continue;
			}
			for (const auto& tile_set : m_pTileSets)
			{
				if (tile_set->Contains(tile))
				{
					int width = tile_set->GetTileWidth(), height = tile_set->GetTileHeight();
					Vector2D_t world_mins, world_maxs;
					Vector2D_t screen_mins, screen_maxs;

					world_mins = { row * width, cols * height };
					world_maxs = { (row + 1) * width, (cols + 1) * height };

					g_pGraphics->WorldToScreen(world_mins, screen_mins);
					g_pGraphics->WorldToScreen(world_maxs, screen_maxs);

					g_pTextureSystem->DrawTile(tile_set, tile, screen_mins.x, screen_mins.y, screen_maxs.x, screen_maxs.y);
					break;
				}
			}
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
