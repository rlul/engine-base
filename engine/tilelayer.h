#pragma once
#include "ilayer.h"
#include "render/itileset.h"
#include <string>
#include <vector>
#include <memory>

class ITileSet;

class CTileLayer : public ILayer
{
	using TileSetList_t = std::vector<std::shared_ptr<ITileSet>>;
	using TileMap_t = std::vector<std::vector<int>>;
public:
	CTileLayer(int ordinal, std::string_view name, TileSetList_t& tile_sets);
	virtual ~CTileLayer() override = default;

	virtual bool Load(const tmx::Layer& layer_handle) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual void Print() const;

	virtual std::string GetName() const override;

private:
	Tile_t TraverseTileMap(int index, int& x, int& y) const;

private:
	int m_iOrdinal;
	std::string m_Name;
	TileSetList_t& m_pTileSets;
	TileMap_t m_iTileMap;
};
