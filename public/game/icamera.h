#pragma once
#include "gamemath.h"

class IBaseEntity;

abstract_class ICamera
{
public:
	virtual ~ICamera() = default;

	virtual bool Setup() = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;

	virtual void ScreenToWorld(float x, float y, float& out_x, float& out_y) const = 0;
	virtual void ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const = 0;
	virtual bool WorldToScreen(float x, float y, float& out_x, float& out_y) const = 0;
	virtual bool WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const = 0;

	virtual bool IsVisible(float x, float y) const = 0;
	virtual bool IsVisible(const Vector2D_t& pos) const = 0;
	virtual bool IsVisible(float x, float y, float w, float h) const = 0;
	virtual bool IsVisible(const Vector2D_t& pos, const Vector2D_t& size) const = 0;
	virtual bool IsVisible(const IBaseEntity* entity) const = 0;

	virtual void GetPos(float& x, float& y) const = 0;
	virtual Vector2D_t GetPos() const = 0;
	virtual void GetSize(float& w, float& h) const = 0;
	virtual Vector2D_t GetSize() const = 0;
	virtual float GetScale() const = 0;
	virtual float GetRotation() const = 0;

	virtual void SetPos(float x, float y) = 0;
	virtual void SetPos(const Vector2D_t& pos) = 0;
	virtual void SetSize(float w, float h) = 0;
	virtual void GetSize(const Vector2D_t& size) = 0;
	virtual void SetScale(float zoom) = 0;
	virtual void SetRotation(float rotation) = 0;
};
