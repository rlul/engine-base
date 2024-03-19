#pragma once

abstract_class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void Render() = 0;
};
