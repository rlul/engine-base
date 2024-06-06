#include "texture.h"
#include <SDL2/SDL.h>

CTexture::CTexture(std::string_view name, SDL_Texture* texture)
	: m_bIsValid(true), m_Name(name), m_pTexture(texture)
{
}

CTexture::~CTexture()
{
	SDL_DestroyTexture(m_pTexture);
}

bool CTexture::IsValid() const
{
	return m_bIsValid;
}

std::string CTexture::GetName() const
{
	return m_Name;
}

CTexture::operator SDL_Texture*() const
{
	return m_pTexture;
}
