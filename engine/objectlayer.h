#pragma once
#include "ilayer.h"
#include "gamemath.h"

class CObjectLayer : public ILayer
{
public:
	CObjectLayer(int ordinal, std::string_view name, Vector2D_t& size);
	virtual ~CObjectLayer() override = default;

	virtual bool Load(const tmx::Layer& layer_handle) override;
	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual std::string GetName() const override;

private:
	int m_iOrdinal;
	std::string m_Name;
	Vector2D_t m_flSize;
};
