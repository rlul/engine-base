#pragma once
#include "game/iviewport.h"
#include <SDL2/SDL.h>

class CGameViewport : public IViewport
{
public:
	CGameViewport();
	virtual ~CGameViewport() override;

	virtual bool Setup(SDL_Renderer* renderer) override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual ICamera* GetCamera() const override { return m_pCamera; }

private:
	SDL_Renderer* m_pRenderer;
	SDL_Rect m_Rect; 
	ICamera* m_pCamera;
};
