#pragma once
#include "game/icamera.h"
#include "gamemath.h"
#include <SDL2/SDL.h>

class CStaticCamera : public ICamera
{
public:
	CStaticCamera();
	virtual ~CStaticCamera() override = default;

	virtual bool Setup(SDL_Renderer* renderer) override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual void ScreenToWorld(float x, float y, float& out_x, float& out_y) const override;
	virtual inline void ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const override { return ScreenToWorld(screen.x, screen.y, world.x, world.y); }
	virtual bool WorldToScreen(float x, float y, float& out_x, float& out_y) const override;
	virtual inline bool WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const override { return WorldToScreen(world.x, world.y, screen.x, screen.y); }

	virtual inline bool IsVisible(float x, float y) const override { return IsVisible(x, y, 1, 1); }
	virtual inline bool IsVisible(const Vector2D_t& pos) const override { return IsVisible(pos.x, pos.y); }
	virtual bool IsVisible(float x, float y, float w, float h) const override;
	virtual inline bool IsVisible(const Vector2D_t& pos, const Vector2D_t& size) const override { return IsVisible(pos.x, pos.y, size.x, size.y); }
	virtual inline bool IsVisible(const IBaseEntity* entity) const override;

	virtual void GetViewport(float& x, float& y, float& w, float& h) const override;
	virtual void SetViewport(float x, float y, float w, float h) override;

	virtual void GetPos(float& x, float& y) const override { x = m_Pos.x; y = m_Pos.y; }
	virtual inline Vector2D_t GetPos() const override { return m_Pos; }
	virtual void GetSize(float& w, float& h) const override { w = m_Viewport.w; h = m_Viewport.h; }
	virtual inline Vector2D_t GetSize() const override { return { m_Viewport.w, m_Viewport.h }; }
	virtual float GetZoom() const override { return m_flZoom; }
	virtual float GetRotation() const override { return m_flRotation; }

	virtual void SetPos(float x, float y) override { m_Pos.x = x; m_Pos.y = y; UpdateTranslateMatrix(); }
	virtual inline void SetPos(const Vector2D_t& pos) override { SetPos(pos.x, pos.y); }
	virtual void SetZoom(float zoom) override { m_flZoom = zoom; UpdateScaleMatrix(); }
	// TODO: fix rotation point
	virtual void SetRotation(float rotation) override { m_flRotation = rotation; UpdateRotationMatrix(); }

protected:
	virtual void UpdateViewMatrix();
	virtual void UpdateTranslateMatrix();
	virtual void UpdateRotationMatrix();
	virtual void UpdateScaleMatrix();

protected:
	SDL_Renderer* m_pRenderer;
	SDL_Rect m_Viewport;
	Vector2D_t m_Pos;
	float m_flZoom;
	float m_flRotation;
	Matrix3x3_t m_ViewMatrix, m_TranslateMatrix, m_RotationMatrix, m_ScaleMatrix;
};
