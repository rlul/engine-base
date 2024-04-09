#pragma once
#include <string>

namespace tmx
{
	class Layer;
}

abstract_class ILayer
{
public:
	virtual ~ILayer() = default;

	virtual bool Load(const tmx::Layer& layer_handle) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;

	virtual void Print() const = 0;

	virtual std::string GetName() const = 0;
};
