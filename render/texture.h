#pragma once
#include "render/itexture.h"
#include <SDL2/SDL.h>

class CTexture : public ITexture
{
public:
	CTexture(std::string_view name, SDL_Texture* texture);
	virtual ~CTexture() override;

	virtual std::string GetName() const override;
	virtual SDL_Texture* GetTexture() const override;

	std::string m_Name;
	SDL_Texture* m_pTexture;
};
