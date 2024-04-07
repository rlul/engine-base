#pragma once
#include "subsystems.h"
#include "core/ifilesystem.h"
#include <tmxlite/Map.hpp>
#include <vector>
#include <sstream>

abstract_class IMapLayer
{
public:
	virtual ~IMapLayer() = default;

	virtual void LoadLayer(const tmx::Layer& layer) = 0;
	virtual void ProcessLayer() = 0;
	virtual void DrawLayer() = 0;
};

class CTileLayer : public IMapLayer
{
public:
	CTileLayer();
	virtual ~CTileLayer() override;

	virtual void LoadLayer(const tmx::Layer& layer) override;
	virtual void ProcessLayer() override;
	virtual void DrawLayer() override;

private:
	const tmx::TileLayer* m_pTmxLayer;
};

class CObjectLayer : public IMapLayer
{
public:
	CObjectLayer();
	virtual ~CObjectLayer() override;

	virtual void LoadLayer(const tmx::Layer& layer) override;
	virtual void ProcessLayer() override;
	virtual void DrawLayer() override;

private:
	const tmx::ObjectGroup* m_pTmxLayer;
};

class CTileMap
{
public:
	CTileMap();
	virtual ~CTileMap();

	virtual bool LoadMap(const char* filename)
	{
		std::ostringstream map_path;

		if (!filename || filename[0] == '\0')
		{
			return false;
		}

		map_path << "scenes/" << filename << ".tmx";

		auto file = g_pFileSystem->Open(map_path.str().c_str(), IFileSystem::OPEN_READ);
		auto file_size = g_pFileSystem->Size(file) + 1;
		char* buffer = new char[file_size];
		g_pFileSystem->Read(file, buffer, file_size);
		m_Map.loadFromString(buffer, R"(C:\Users\Ivan\source\engine-base\game\demo\scenes\)");

		for (const auto& layer : m_Map.getLayers())
		{
			if (layer->getType() == tmx::Layer::Type::Tile)
			{
				auto pTileLayer = new CTileLayer();
				pTileLayer->LoadLayer(*layer);
				m_pLayers.push_back(pTileLayer);
			}
			else if (layer->getType() == tmx::Layer::Type::Object)
			{
				auto pObjectLayer = new CObjectLayer();
				pObjectLayer->LoadLayer(*layer);
				m_pLayers.push_back(pObjectLayer);
			}
		}
	}
	virtual void ProcessMap()
	{
		for (auto& layer : m_pLayers)
			layer->ProcessLayer();
	}

	virtual void DrawMap()
	{
		for (auto& layer : m_pLayers)
			layer->DrawLayer();
	}

private:
	tmx::Map m_Map;
	std::vector<IMapLayer*> m_pLayers;
};
