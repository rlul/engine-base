#include "sprite.h"
#include "subsystems.h"
#include "render/itexture.h"
#include "render/itexturesystem.h"
#include <SDL2/SDL.h>


CSprite::CSprite(std::string_view name, const std::shared_ptr<ITexture>& texture, const SpriteData_t& sprite_data)
	: m_Name(name), m_pTexture(texture), m_nColumns(sprite_data.columns), m_nRows(sprite_data.rows)
{
	int texture_width, texture_height;
	if (SDL_QueryTexture(*texture, NULL, NULL, &texture_width, &texture_height))
	{
		printf("%s\n", SDL_GetError());
	}
	m_iFrameWidth = texture_width / sprite_data.columns;
	m_iFrameHeight = texture_height / sprite_data.rows;

	for (const auto& animation : sprite_data.animations)
	{
		Animation_t anim;
		anim.name = animation.name;
		anim.frame_rate = animation.frame_rate;
		anim.frames = animation.frames;

		m_pAnimations.push_back(anim);
	}
}

CSprite::~CSprite()
{
	g_pTextureSystem->UnloadTexture(m_pTexture);
}

std::string CSprite::GetName() const
{
	return m_Name;
}

std::shared_ptr<ITexture> CSprite::GetTexture() const
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
	if (animation_id < 0 || animation_id >= m_pAnimations.size())
	{
		return 0;
	}
	return m_pAnimations[animation_id].frames.size();
}

int CSprite::GetFrameRate(int animation_id) const
{
	if (animation_id < 0 || animation_id >= m_pAnimations.size())
	{
		return 0;
	}
	return m_pAnimations[animation_id].frame_rate;
}

int CSprite::GetFrame(int index, int animation_id) const
{
	if (animation_id < 0 || animation_id >= m_pAnimations.size())
	{
		return -1;
	}
	if (index < 0 || index >= m_pAnimations[animation_id].frames.size())
	{
		return -1;
	}
	return m_pAnimations[animation_id].frames[index];
}

int CSprite::GetAnimationId(const char* name) const
{
	for (size_t i = 0; i < m_pAnimations.size(); i++)
	{
		if (m_pAnimations[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

bool CSprite::IsAnimationValid(int animation_id) const
{
	return animation_id >= 0 && animation_id < m_pAnimations.size();
}

bool CSprite::IsAnimationValid(const char* name) const
{
	return GetAnimationId(name) != -1;
}
