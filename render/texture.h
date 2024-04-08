#pragma once
#include "render/itexture.h"
#include <SDL2/SDL.h>

class CTexture : public ITexture
{
public:
	CTexture(const char* name, SDL_Texture* texture);
	virtual ~CTexture() override;

	virtual const char* GetName() const override;
	virtual SDL_Texture* GetTexture() const override;

	const char* m_pszName;
	SDL_Texture* m_pTexture;
};
