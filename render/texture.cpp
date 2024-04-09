#include "texture.h"
#include <SDL2/SDL.h>

CTexture::CTexture(std::string_view name, SDL_Texture* texture)
	: m_Name(name), m_pTexture(texture)
{
}

CTexture::~CTexture()
{
	SDL_DestroyTexture(m_pTexture);
}

std::string CTexture::GetName() const
{
	return m_Name;
}

CTexture::operator SDL_Texture*() const
{
	return m_pTexture;
}
