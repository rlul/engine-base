#include "render/ispritesystem.h"
#include "core/ifilesystem.h"
#include "subsystem.h"
#include "sprite.h"
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <sstream>
#include <string>
#include <unordered_map>

class CSpriteSystem : public ISpriteSystem
{
	friend class ISprite;
	friend class CSprite;

public:
	CSpriteSystem() = default;
	~CSpriteSystem() override = default;

	bool Setup(SDL_Renderer* renderer) override;
	void Shutdown() override;
	const char* GetSystemName() const override { return SPRITE_SYSTEM_VERSION; }

	ISprite* LoadSprite(const char* filename) override;
	void UnloadSprite(ISprite* sprite) override;
	bool DrawSprite(ISprite* sprite, int x, int y) override;

private:
	virtual SDL_Texture* LoadTexture(const char* filename);
	virtual void UnloadTexture(const char* filename);

private:
	SDL_Renderer* m_pRenderer;
	std::vector<CSprite*> m_LoadedSprites;
	std::unordered_map<std::string, SDL_Texture*> m_LoadedTextures;

};

CSpriteSystem g_SpriteSystem;
CREATE_SINGLE_SYSTEM( CSpriteSystem, ISpriteSystem, SPRITE_SYSTEM_VERSION, g_SpriteSystem );

bool CSpriteSystem::Setup(SDL_Renderer* renderer)
{
	m_pRenderer = renderer;
	return true;
}

void CSpriteSystem::Shutdown()
{

}

ISprite* CSpriteSystem::LoadSprite(const char* filename)
{
	std::ostringstream sprite_path;
	FileHandle_t file;
	unsigned file_size;
	char* buf;
	nlohmann::json sprite_data;
	char* texture_path;
	int sprite_columns, sprite_rows;

	if (!filename || filename[0] == '\0')
	{
		return nullptr;
	}

	for (const auto & sprite : m_LoadedSprites)
	{
		if (strcmp(sprite->GetPath(), filename) == 0)
		{
			return sprite;
		}
	}

	sprite_path << "sprites/" << filename << ".json";

	file = g_pFileSystem->Open(sprite_path.str().c_str(), IFileSystem::OPEN_READ);
	if (!file)
	{
		return nullptr;
	}
	file_size = g_pFileSystem->Size(file) + 1;
	buf = new char[file_size] { 0, };
	g_pFileSystem->Read(file, buf, file_size);

	printf("%s\n", buf);

	sprite_data = nlohmann::json::parse(buf);
	texture_path = new char[260] {0, };
	strcpy(texture_path, static_cast<std::string>(sprite_data["texture"]).c_str());
	sprite_columns = sprite_data["columns"];
	sprite_rows = sprite_data["rows"];

	delete[] buf;
	g_pFileSystem->Close(file);

	SDL_Texture* texture = LoadTexture(texture_path);

	if (!texture)
	{
		return nullptr;
	}

	CSprite* sprite = new CSprite(filename, texture);
	m_LoadedSprites.push_back(sprite);

	return sprite;
}

void CSpriteSystem::UnloadSprite(ISprite* sprite)
{
	// TODO: check if spite's texture is still in use by other sprites and unload it if not
}

bool CSpriteSystem::DrawSprite(ISprite* sprite, int x, int y)
{
	SDL_Rect src{ 0,0,16, 16 }, dst{ x, y, 16*4, 16*4 };

	if (!sprite)
	{
		return false;
	}

	SDL_RenderCopy(m_pRenderer, sprite->GetTexture(), &src, &dst);

	return true;
}

SDL_Texture* CSpriteSystem::LoadTexture(const char* filename)
{
	std::ostringstream texture_path;
	FileHandle_t file;
	unsigned file_size;
	char* buf;
	SDL_RWops* rw;
	SDL_Surface* surface;
	SDL_Texture* texture;

	if (!filename || filename[0] == '\0')
	{
		return nullptr;
	}

	if (m_LoadedTextures.contains(filename))
	{
		return m_LoadedTextures[filename];
	}

	texture_path << "textures/" << filename << ".png";

	file = g_pFileSystem->Open(texture_path.str().c_str(), IFileSystem::OPEN_READ);
	file_size = g_pFileSystem->Size(file);
	buf = new char[file_size] { 0, };
	g_pFileSystem->Read(file, buf, file_size);

	rw = SDL_RWFromMem(buf, file_size);
	surface = IMG_Load_RW(rw, 1);

	delete[] buf;
	g_pFileSystem->Close(file);

	if (!surface)
	{
		printf("Failed to load surface %s\n", filename);
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	if (!texture)
	{
		printf("Failed to create texture from surface %s\n", filename);
		return nullptr;
	}

	SDL_FreeSurface(surface);
	m_LoadedTextures[filename] = texture;

	return texture;
}

void CSpriteSystem::UnloadTexture(const char* filename)
{
	if (m_LoadedTextures.contains(filename))
	{
		SDL_DestroyTexture(m_LoadedTextures[filename]);
		m_LoadedTextures.erase(filename);
	}
}
