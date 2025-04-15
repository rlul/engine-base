#pragma once

class SDL_Renderer;
class ICamera;

abstract_class IViewport
{
public:
	virtual ~IViewport() = default;

	virtual bool Setup(SDL_Renderer* renderer) = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;

	virtual ICamera* GetCamera() const = 0;
};
