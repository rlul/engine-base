#include "texture.h"
#include <SDL2/SDL.h>

CTexture::CTexture(const char* name, SDL_Texture* texture)
	: m_pszName(name), m_pTexture(texture)
{
}

CTexture::~CTexture()
{
	SDL_DestroyTexture(m_pTexture);
}

const char* CTexture::GetName() const
{
	return m_pszName;
}

SDL_Texture* CTexture::GetTexture() const
{
	return m_pTexture;
}
