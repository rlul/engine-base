#pragma once
#include <string>
#include <memory>

typedef int Tile_t;

class ITexture;

abstract_class ITileSet
{
public:
	virtual ~ITileSet() = default;

	virtual void GetTileRect(Tile_t tile_id, int& x, int& y, int& w, int& h) const = 0;
	virtual bool Contains(Tile_t tile_id) const = 0;

	virtual std::string GetName() const = 0;
	virtual std::shared_ptr<ITexture> GetTexture() const = 0;
	virtual int GetFirst() const = 0;
	virtual int GetLast() const = 0;
	virtual int GetColumns() const = 0;
	virtual int GetRows() const = 0;
	virtual int GetTileWidth() const = 0;
	virtual int GetTileHeight() const = 0;
};
