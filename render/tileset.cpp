#include "tileset.h"
#include "subsystems.h"
#include "render/itexturesystem.h"
#include <tmxlite/Tileset.hpp>

CTileSet::CTileSet(const tmx::Tileset& tileset)
	: m_Name(tileset.getName()),
	  m_iFirst(tileset.getFirstGID()),
	  m_iLast(tileset.getFirstGID() + tileset.getTileCount())
{
	auto texture = g_pTextureSystem->LoadTexture(tileset.getImagePath().c_str());
	m_pTexture = texture;

	m_nColumns = tileset.getColumnCount();
	if (m_nColumns == 0)
		return;

	m_nRows = (m_iLast - m_iFirst) / m_nColumns;
	m_iTileWidth = tileset.getTileSize().x;
	m_iTileHeight = tileset.getTileSize().y;

}

CTileSet::~CTileSet()
{
	g_pTextureSystem->UnloadTexture(m_pTexture);
}

void CTileSet::GetTileRect(Tile_t tile_id, int& x, int& y, int& w, int& h) const
{
	int tile_x = (tile_id - m_iFirst) % m_nColumns;
	int tile_y = (tile_id - m_iFirst) / m_nColumns;
	x = tile_x * m_iTileWidth;
	y = tile_y * m_iTileHeight;
	w = m_iTileWidth;
	h = m_iTileHeight;
}

bool CTileSet::Contains(Tile_t tile_id) const
{
	return tile_id >= m_iFirst && tile_id < m_iLast;
}

std::string CTileSet::GetName() const
{
	return m_Name;
}

std::shared_ptr<ITexture> CTileSet::GetTexture() const
{
	return m_pTexture;
}

Tile_t CTileSet::GetFirst() const
{
	return m_iFirst;
}

Tile_t CTileSet::GetLast() const
{
	return m_iLast;
}

int CTileSet::GetColumns() const
{
	return m_nColumns;
}

int CTileSet::GetRows() const
{
	return m_nRows;
}

int CTileSet::GetTileWidth() const
{
	return m_iTileWidth;
}

int CTileSet::GetTileHeight() const
{
	return m_iTileHeight;
}
