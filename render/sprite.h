#pragma once
#include "render/isprite.h"

class CSprite : public ISprite
{
public:
	CSprite(const char* path, SDL_Texture* texture);
	~CSprite() override = default;

	const char* GetPath() const override;
	SDL_Texture* GetTexture() const override;

private:
	const char* m_pszPath;
	SDL_Texture* m_pTexture;
	// m_Frames, m_uFrameCount, m_uFrameWidth, m_uFrameHeight
};
