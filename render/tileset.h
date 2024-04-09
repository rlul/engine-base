#pragma once
#include "render/itileset.h"

namespace tmx
{
	class Tileset;
}

class ITexture;

class CTileSet : public ITileSet
{
public:
	CTileSet(const tmx::Tileset& tileset);
	virtual ~CTileSet() override;

	virtual void GetTileRect(Tile_t tile_id, int& x, int& y, int& w, int& h) const override;
	virtual bool Contains(Tile_t tile_id) const override;

	virtual std::string GetName() const override;
	virtual std::shared_ptr<ITexture> GetTexture() const override;
	virtual Tile_t GetFirst() const override;
	virtual Tile_t GetLast() const override;
	virtual int GetColumns() const override;
	virtual int GetRows() const override;
	virtual int GetTileWidth() const override;
	virtual int GetTileHeight() const override;

private:
	std::string m_Name;
	std::shared_ptr<ITexture> m_pTexture;
	Tile_t m_iFirst, m_iLast;
	int m_nColumns, m_nRows;
	int m_iTileWidth, m_iTileHeight;
};
