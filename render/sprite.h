#pragma once
#include "render/isprite.h"
#include <vector>
#include <string>

struct SpriteData_t
{
	struct AnimationData_t
	{
		std::string name;
		int frame_rate;
		std::vector<int> frames;
	};
	std::string texture_id;
	int columns, rows;
	std::vector<AnimationData_t> animations;
};

class CSprite : public ISprite
{
	struct Animation_t
	{
		std::string name;
		int frame_rate;
		std::vector<int> frames;
	};

public:
	CSprite(const char* name, const std::shared_ptr<ITexture>& texture, const SpriteData_t& sprite_data);
	virtual ~CSprite() override;

	virtual const char* GetName() const override;
	virtual std::shared_ptr<ITexture> GetTexture() const override;
	virtual void GetSpriteSize(int& columns, int& rows) const override;

	virtual void GetFrameSize(int& width, int& height) const override;
	virtual int GetFrameCount(int animation_id) const override;
	virtual int GetFrameRate(int animation_id) const override;
	virtual int GetFrame(int index, int animation_id) const override;

	virtual int GetAnimationId(const char* name) const override;
	virtual bool IsAnimationValid(int animation_id) const override;
	virtual bool IsAnimationValid(const char* name) const override;

private:
	const char* m_pszName;
	std::shared_ptr<ITexture> m_pTexture;
	int m_iFrameWidth, m_iFrameHeight;
	int m_nColumns, m_nRows;
	std::vector<Animation_t> m_pAnimations;
};
