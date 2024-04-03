#pragma once
#include "subsystems.h"
#include "gamemath.h"

#define GRAPHICS_SYSTEM_VERSION "Graphics001"

class SDL_Window;
class SDL_Renderer;

abstract_class IGraphics : public IAppSystem
{
public:
	virtual ~IGraphics() = default;

	virtual bool Setup() = 0;

	virtual bool Frame() = 0;
	virtual void ProcessEvent(void* sdl_event) = 0;

	virtual void ScreenToWorld(float x, float y, float& out_x, float& out_y) const = 0;
	virtual inline void ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const = 0;
	virtual bool WorldToScreen(float x, float y, float& out_x, float& out_y) const = 0;
	virtual inline bool WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const = 0;

	virtual SDL_Window* GetWindow() const = 0;
	virtual SDL_Renderer* GetRenderer() const = 0;
	virtual void GetScreenSize(int& w, int& h) const = 0;
};
