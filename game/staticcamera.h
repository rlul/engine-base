#pragma once
#include "game/icamera.h"
#include "render/renderview.h"
#include "gamemath.h"
#include <SDL2/SDL.h>

class CStaticCamera : public ICamera
{
public:
	CStaticCamera();
	virtual ~CStaticCamera() override;

	virtual bool Setup() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual void ScreenToWorld(float x, float y, float& out_x, float& out_y) const override;
	virtual inline void ScreenToWorld(const Vector2D_t& screen, Vector2D_t& world) const override { return ScreenToWorld(screen.x, screen.y, world.x, world.y); }
	virtual bool WorldToScreen(float x, float y, float& out_x, float& out_y) const override;
	virtual inline bool WorldToScreen(const Vector2D_t& world, Vector2D_t& screen) const override { return WorldToScreen(world.x, world.y, screen.x, screen.y); }

	virtual bool IsVisible(float x, float y) const override { return IsVisible(x, y, 1, 1); }
	virtual bool IsVisible(const Vector2D_t& pos) const override { return IsVisible(pos.x, pos.y); }
	virtual bool IsVisible(float x, float y, float w, float h) const override;
	virtual bool IsVisible(const Vector2D_t& pos, const Vector2D_t& size) const override { return IsVisible(pos.x, pos.y, size.x, size.y); }
	virtual inline bool IsVisible(const IBaseEntity* entity) const override;

	virtual void GetPos(float& x, float& y) const override { x = m_pRenderView->m_Pos.x; y = m_pRenderView->m_Pos.y; }
	virtual Vector2D_t GetPos() const override { return m_pRenderView->m_Pos; }
	virtual void GetSize(float& w, float& h) const override { w = m_pRenderView->m_Size.x; h = m_pRenderView->m_Size.y; }
	virtual Vector2D_t GetSize() const override { return m_pRenderView->m_Size; }
	virtual float GetScale() const override { return m_pRenderView->m_flScale; }
	virtual float GetRotation() const override { return m_pRenderView->m_flRotation; }

	virtual void SetPos(float x, float y) override { m_pRenderView->m_Pos.x = x; m_pRenderView->m_Pos.y = y; UpdateViewMatrix(); }
	virtual void SetPos(const Vector2D_t& pos) override { SetPos(pos.x, pos.y); }
	virtual void SetSize(float w, float h) override { m_pRenderView->m_Size.x = w; m_pRenderView->m_Size.y = h; }
	virtual void GetSize(const Vector2D_t& size) override { m_pRenderView->m_Size = size; }
	virtual void SetScale(float zoom) override { m_pRenderView->m_flScale = zoom; UpdateViewMatrix(); }
	// TODO: fix rotation point
	virtual void SetRotation(float rotation) override { m_pRenderView->m_flRotation = rotation; UpdateViewMatrix(); }

protected:
	virtual void UpdateViewMatrix();

protected:
	CRenderView* m_pRenderView;
};
