#include "sprite.h"
#include <SDL2/SDL.h>

CSprite::CSprite(const char* path, SDL_Texture* texture)
	: m_pszPath(path), m_pTexture(texture)
{
}

const char* CSprite::GetPath() const
{
	return m_pszPath;
}

SDL_Texture* CSprite::GetTexture() const
{
	return m_pTexture;
}

