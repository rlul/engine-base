#pragma once

namespace tmx
{
	class Map;
}

abstract_class ITileMap
{
public:
	virtual ~ITileMap() = default;

	virtual bool Load(const tmx::Map& map) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;
};
