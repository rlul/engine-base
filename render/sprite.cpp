#include "sprite.h"
#include <SDL2/SDL.h>
#include <cstring>

CSprite::CSprite()
	: m_pszPath(nullptr), m_pTexture(nullptr), m_iFrameWidth(0), m_iFrameHeight(0), m_nColumns(0), m_nRows(0)
	, m_pAnimations(nullptr), m_nAnimationCount(0)
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

SDL_Texture* CSprite::GetTexture() const
{
	return m_pTexture;
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

int CSprite::GetFrameCount(int animation_id) const
{
	if (!IsAnimationValid(animation_id))
		return 0;

	return m_pAnimations[animation_id].frame_count;
}

float CSprite::GetFrameRate(int animation_id) const
{
	if (!IsAnimationValid(animation_id))
		return 0.f;

	return m_pAnimations[animation_id].frame_rate;
}

int CSprite::GetFrame(int index, int animation_id) const
{
	if (!IsAnimationValid(animation_id))
		return 0;

	if (index < 0 || index >= m_pAnimations[animation_id].frame_count)
		return 0;

	return m_pAnimations[animation_id].frames[index];
}

int CSprite::GetAnimationId(const char* animation_name) const
{
	for (int i = 0; i < m_nAnimationCount; i++)
	{
		if (std::strcmp(m_pAnimations[i].name, animation_name) == 0)
		return i;
	}

	return -1;
}

bool CSprite::IsAnimationValid(const char* animation_name) const
{
	for (int i = 0; i < m_nAnimationCount; i++)
	{
		if (std::strcmp(m_pAnimations[i].name, animation_name) == 0)
		return true;
	}

	return false;
}

bool CSprite::IsAnimationValid(int animation_id) const
{
	return animation_id >= 0 && animation_id < m_nAnimationCount;
}
