#pragma once
#include "engine/itilemap.h"
#include "render/itileset.h"
#include <vector>

class ILayer;

class CTileMap : public ITileMap
{
public:
	enum class RenderOrder_t
	{
		RightDown,
		RightUp,
		LeftDown,
		LeftUp
	};

public:
	CTileMap(std::string_view name);
	virtual ~CTileMap() override = default;

	virtual bool Load(const tmx::Map& map) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

private:
	virtual bool LoadTileSets(const tmx::Map& map);
	virtual bool LoadLayers(const tmx::Map& map);

private:
	std::string m_Name;
	RenderOrder_t m_RenderOrder;
	std::vector<std::shared_ptr<ITileSet>> m_pTileSets;
	std::vector<ILayer*> m_pLayers;
};
