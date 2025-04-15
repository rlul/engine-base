#pragma once
#include "render/itexturesystem.h"
#include "sprite.h"
#include "tileset.h"
#include "texture.h"
#include <vector>

class CTextureSystem : public ITextureSystem
{
public:
	CTextureSystem();
	virtual ~CTextureSystem() override;

	virtual bool Setup(SDL_Renderer* renderer) override;
	virtual void Shutdown() override;

	virtual void Clear() override;
	virtual void PrintReport() const override;

	virtual void DrawSprite(const std::shared_ptr<ISprite>& sprite, int animation_index, int frame_index, float x1, float y1, float x2, float y2, float rotation) override;
	virtual std::shared_ptr<ISprite> LoadSprite(const char* name) override;
	virtual void UnloadSprite(const char* sprite_id) override;
	virtual void UnloadSprite(const std::shared_ptr<ISprite>& sprite) override;

	virtual void DrawTile(const std::shared_ptr<ITileSet>& tileset, Tile_t tile_id, float x1, float y1, float x2, float y2) override;
	virtual std::shared_ptr<ITileSet> LoadTileSet(const tmx::Tileset& tileset_handle) override;
	virtual void UnloadTileSet(const char* tileset_id) override;
	virtual void UnloadTileSet(const std::shared_ptr<ITileSet>& tileset) override;

	virtual std::shared_ptr<ITexture> LoadTexture(const char* name) override;
	virtual void UnloadTexture(const char* texture_id) override;
	virtual void UnloadTexture(const std::shared_ptr<ITexture>& texture) override;

private:
	virtual SpriteData_t ParseSpriteData(const char* data) const;

private:
	SDL_Renderer* m_pRenderer;
	std::vector<std::pair<std::shared_ptr<ISprite>, unsigned>> m_pLoadedSprites;
	std::vector<std::pair<std::shared_ptr<ITexture>, unsigned>> m_pLoadedTextures;
	SDL_Surface* m_pMissingSurface;
};
