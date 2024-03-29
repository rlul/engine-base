#pragma once
#include "render/isprite.h"
#include <SDL2/SDL.h>

class CSprite : public ISprite
{
	friend class CSpriteSystem;

	struct Animation_t
	{
		char name[64];
		int frames[256];
		int frame_count;
		float frame_rate;
	};

public:
	CSprite();
	virtual ~CSprite() override;

	virtual const char* GetPath() const override;
	virtual SDL_Texture* GetTexture() const override;

	virtual void GetSpriteSize(int& columns, int& rows) const override;
	virtual void GetFrameSize(int& width, int& height) const override;

	virtual int GetFrameCount(int animation_id) const override;
	virtual float GetFrameRate(int animation_id) const override;
	virtual int GetFrame(int index, int animation_id) const override;

	virtual int GetAnimationId(const char* animation_name) const override;
	virtual bool IsAnimationValid(const char* animation_name) const override;
	virtual bool IsAnimationValid(int animation_id) const override;

private:
	const char* m_pszPath;
	SDL_Texture* m_pTexture;
	int m_iFrameWidth, m_iFrameHeight;
	int m_nColumns, m_nRows;
	Animation_t* m_pAnimations;
	int m_nAnimationCount;
};
