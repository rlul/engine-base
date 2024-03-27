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
	~CSprite() override;

	const char* GetPath() const override;
	void GetSpriteSize(int& columns, int& rows) const override;
	void GetFrameSize(int& width, int& height) const override;
	int GetFrameCount() const override;
	float GetFrameRate() const override;
	void SetFrameRate(float frame_rate) override;
	int GetFrame(int index) const override;
	SDL_Texture* GetTexture() const override;
	const char* GetCurrentAnimation() const override;
	bool SetCurrentAnimation(const char* name) override;

private:
	const char* m_pszPath;
	SDL_Texture* m_pTexture;
	int m_iFrameWidth, m_iFrameHeight;
	int m_nColumns, m_nRows;
	Animation_t* m_pAnimations;
	int m_nAnimationCount;
	int m_nCurrentAnimation;
};
