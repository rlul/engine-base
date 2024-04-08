#pragma once
#include "subsystems.h"
#include <memory>

#define TEXTURE_SYSTEM_VERSION "TextureSystem001"

class SDL_Renderer;
class ITexture;
class ISprite;

abstract_class ITextureSystem : public IAppSystem
{
public:
	virtual ~ITextureSystem() = default;

	virtual bool Setup(SDL_Renderer* renderer) = 0;
	virtual void Shutdown() override = 0;
	virtual const char* GetSystemName() const override { return TEXTURE_SYSTEM_VERSION; }

	virtual void Clear() = 0;
	virtual void PrintReport() const = 0;

	virtual void DrawSprite(const std::shared_ptr<ISprite>& sprite, int animation_index, int frame_index, int x1, int y1, int x2, int y2, float rotation) = 0;
	virtual std::shared_ptr <ISprite> LoadSprite(const char* sprite_id) = 0;
	virtual void UnloadSprite(const char* sprite_id) = 0;
	virtual void UnloadSprite(const std::shared_ptr<ISprite>& sprite) = 0;

	virtual std::shared_ptr<ITexture> LoadTexture(const char* texture_id) = 0;
	virtual void UnloadTexture(const char* texture_id) = 0;
	virtual void UnloadTexture(const std::shared_ptr<ITexture>& texture) = 0;
};
