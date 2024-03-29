#pragma once
#include "render/ispritesystem.h"
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class CSprite;

class CSpriteSystem : public ISpriteSystem
{
	struct SpriteData_t
	{
		struct AnimationData_t
		{
			char name[64];
			int frames[256];
			int frame_count;
			float frame_rate;
		};

		char texture_path[128];
		int columns;
		int rows;
		int animation_count;
		AnimationData_t animations[32];
	};

public:
	CSpriteSystem() = default;
	virtual ~CSpriteSystem() override = default;

	virtual bool Setup(SDL_Renderer* renderer) override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return SPRITE_SYSTEM_VERSION; }

	virtual ISprite* LoadSprite(const char* filename) override;
	virtual void UnloadSprite(ISprite* sprite) override;
	virtual bool DrawSprite(ISprite* sprite, int x, int y, float scale) override;
	virtual bool DrawSpriteEx(ISprite* sprite, int animation_index, int frame_index, int x, int y, float scale_x, float scale_y) override;

private:
	virtual SDL_Texture* LoadTexture(const char* filename);
	virtual void UnloadTexture(const char* filename);

	virtual SpriteData_t ParseSpriteData(nlohmann::json& json_data);
	virtual bool ValidateSpriteData(SpriteData_t& sprite_data);

private:
	SDL_Renderer* m_pRenderer;
	std::vector<CSprite*> m_LoadedSprites;
	std::unordered_map<std::string, SDL_Texture*> m_LoadedTextures;

};
