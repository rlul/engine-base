#include "sprite.h"
#include <SDL2/SDL.h>
#include <cstring>

CSprite::CSprite()
	: m_pszPath(nullptr), m_pTexture(nullptr), m_iFrameWidth(0), m_iFrameHeight(0), m_nColumns(0), m_nRows(0)
	, m_pAnimations(nullptr), m_nAnimationCount(0), m_nCurrentAnimation(0)
{
}

CSprite::~CSprite()
{
	for (int i = 0; i < m_nAnimationCount; i++)
	{
		delete[] m_pAnimations[i].frames;
	}

	delete[] m_pAnimations;
}

const char* CSprite::GetPath() const
{
	return m_pszPath;
}

void CSprite::GetSpriteSize(int& columns, int& rows) const
{
	columns = m_nColumns;
	rows = m_nRows;
}

void CSprite::GetFrameSize(int& width, int& height) const
{
	width = m_iFrameWidth;
	height = m_iFrameHeight;
}

int CSprite::GetFrameCount() const
{
	return m_pAnimations[m_nCurrentAnimation].frame_count;
}

float CSprite::GetFrameRate() const
{
	return m_pAnimations[m_nCurrentAnimation].frame_rate;
}

void CSprite::SetFrameRate(float frame_rate)
{
	if (frame_rate < 0)
	{
		return;
	}

	m_pAnimations[m_nCurrentAnimation].frame_rate = frame_rate;
}

int CSprite::GetFrame(int index) const
{
	if (index < 0 || index >= GetFrameCount())
	{
		return -1;
	}
	return m_pAnimations[m_nCurrentAnimation].frames[index];
}

SDL_Texture* CSprite::GetTexture() const
{
	return m_pTexture;
}

const char* CSprite::GetCurrentAnimation() const
{
	return m_pAnimations[m_nCurrentAnimation].name;
}

bool CSprite::SetCurrentAnimation(const char* name)
{
	for (int i = 0; i < m_nAnimationCount; i++)
	{
		if (strcmp(m_pAnimations[i].name, name) == 0)
		{
			m_nCurrentAnimation = i;
			return true;
		}
	}

	return false;
}
