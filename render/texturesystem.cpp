#include "texturesystem.h"
#include "sprite.h"
#include "texture.h"
#include "core/ifilesystem.h"
#include "subsystem.h"
#include "subsystems.h"
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <tmxlite/Tileset.hpp>
#include <sstream>

CTextureSystem g_TextureSystem;
CREATE_SINGLE_SYSTEM( CTextureSystem, ITextureSystem, TEXTURE_SYSTEM_VERSION, g_TextureSystem );


CTextureSystem::CTextureSystem()
{
	
}

CTextureSystem::~CTextureSystem()
{
	
}

bool CTextureSystem::Setup(SDL_Renderer* renderer)
{
	if (!renderer)
		return false;

	m_pRenderer = renderer;

	m_pMissingSurface = SDL_CreateRGBSurface(0, 32, 32, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	Uint32 pink = SDL_MapRGB(m_pMissingSurface->format, 255, 105, 180); // Pink color
	SDL_FillRect(m_pMissingSurface, nullptr, pink);

	return true;
}

void CTextureSystem::Shutdown()
{
	
}

void CTextureSystem::Clear()
{

}

void CTextureSystem::PrintReport() const
{
	printf("Loaded textures:\n");
    for (auto& loaded_texture : m_pLoadedTextures)
	{
		printf("%s: %u\n", loaded_texture.first->GetName().c_str(), loaded_texture.second);
	}
	printf("Loaded sprites:\n");
	for (auto& loaded_sprite : m_pLoadedSprites)
	{
		printf("%s: %u\n", loaded_sprite.first->GetName().c_str(), loaded_sprite.second);
	}
}

void CTextureSystem::DrawSprite(const std::shared_ptr<ISprite>& sprite, int animation_index, int frame_index, float x1, float y1, float x2, float y2, float rotation)
{
	SDL_Rect src_rect;
	SDL_FRect dest_rect;
	int columns, rows;
	int frame_width, frame_height;
	int frame;

	if (!sprite) return;

	if (sprite->GetTexture()->IsValid())
	{
		sprite->GetSpriteSize(columns, rows);
		sprite->GetFrameSize(frame_width, frame_height);
		frame = sprite->GetFrame(frame_index, animation_index);
		if (frame < 0) return;
		src_rect = { (frame % columns) * frame_width, (frame / columns) * frame_height, frame_width, frame_height };
	}
	else
	{
		src_rect = { 0, 0, 32, 32 };
	}

	dest_rect = { x1, y1, x2 - x1, y2 - y1 };

	SDL_RenderCopyExF(m_pRenderer, *sprite->GetTexture(), &src_rect, &dest_rect, rotation, NULL, SDL_FLIP_NONE);
}

std::shared_ptr<ISprite> CTextureSystem::LoadSprite(const char* name)
{
	for (auto& loaded_sprite : m_pLoadedSprites)
	{
		if (loaded_sprite.first->GetName() == name)
		{
			++loaded_sprite.second;
			return loaded_sprite.first;
		}
	}

	std::ostringstream sprite_path;
	sprite_path << "sprites/" << name << ".json";

	auto file = g_pFileSystem->Open(sprite_path.str().c_str(), IFileSystem::OPEN_READ);
	auto file_size = g_pFileSystem->Size(file) + 1;
	auto file_data = new char[file_size] { 0, };
	g_pFileSystem->Read(file, file_data, file_size);
	SpriteData_t sprite_data;
	if (file_size != 1)
	{
		sprite_data = ParseSpriteData(file_data);
	}
	else
	{
		printf("Failed to load sprite %s\n", name);
	}
	delete[] file_data;
	g_pFileSystem->Close(file);

	auto texture = LoadTexture(sprite_data.texture_id.c_str());
	if (!texture)
	{
		return nullptr;
	}

	auto sprite = std::make_shared<CSprite>(name, texture, sprite_data);

	m_pLoadedSprites.emplace_back(sprite, 1);
	return sprite;
}

void CTextureSystem::UnloadSprite(const char* sprite_id)
{
	erase_if(m_pLoadedSprites, [sprite_id](std::pair<std::shared_ptr<ISprite>, unsigned>& sprite) -> bool
		{
			return sprite.first->GetName() == sprite_id && --sprite.second == 0;
		});
}

void CTextureSystem::UnloadSprite(const std::shared_ptr<ISprite>& sprite)
{
	UnloadSprite(sprite->GetName().c_str());
}

void CTextureSystem::DrawTile(const std::shared_ptr<ITileSet>& tileset, Tile_t tile_id, float x1, float y1, float x2, float y2)
{
	if (!tileset)
		return;

	auto texture = tileset->GetTexture();
	if (!texture)
		return;

	SDL_Rect src_rect;
	SDL_FRect dest_rect;
	tileset->GetTileRect(tile_id, src_rect.x, src_rect.y, src_rect.w, src_rect.h);
	dest_rect = { x1, y2, x2 - x1, y1 - y2 };

	SDL_RenderCopyExF(m_pRenderer, *texture, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_NONE);
}

std::shared_ptr<ITileSet> CTextureSystem::LoadTileSet(const tmx::Tileset& tileset_handle)
{
	auto tileset = std::make_shared<CTileSet>(tileset_handle);
	return tileset;
}

void CTextureSystem::UnloadTileSet(const char* tileset_id)
{

}

void CTextureSystem::UnloadTileSet(const std::shared_ptr<ITileSet>& tileset)
{

}

std::shared_ptr<ITexture> CTextureSystem::LoadTexture(const char* name)
{
	for (auto& loaded_texture : m_pLoadedTextures)
	{
		if (loaded_texture.first->GetName() == name)
		{
			++loaded_texture.second;
			return loaded_texture.first;
		}
	}

	FileHandle_t file_handle = nullptr;
	if (std::filesystem::path(name).is_absolute())
	{
		file_handle = g_pFileSystem->OpenFullPath(name, IFileSystem::OPEN_READ);
	}
	else
	{
		std::ostringstream texture_path;
		texture_path << "textures/" << name << ".png";
		file_handle = g_pFileSystem->Open(texture_path.str().c_str(), IFileSystem::OPEN_READ);
	}

	SDL_Surface* surface = nullptr;

	if (file_handle)
	{
		auto file_size = g_pFileSystem->Size(file_handle);
		auto file_data = new char[file_size];
		g_pFileSystem->Read(file_handle, file_data, file_size);

		auto rw = SDL_RWFromConstMem(file_data, file_size);
		SDL_RWseek(rw, 0, RW_SEEK_SET);
		surface = IMG_LoadPNG_RW(rw);
		SDL_RWclose(rw);


		delete[] file_data;
		g_pFileSystem->Close(file_handle);
	}

	if (!surface)
	{
		printf("Failed to load surface %s\n", name);
		surface = m_pMissingSurface;
		//return nullptr;
	}

	auto texure_handle = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	if (!texure_handle)
	{
		printf("Failed to create texture from surface %s\n", name);
		return nullptr;
	}

	auto texture = std::make_shared<CTexture>(name, texure_handle);
	if (!texture)
	{
		return nullptr;
	}

	if (surface == m_pMissingSurface)
	{
		texture->m_bIsValid = false;
	}

	m_pLoadedTextures.emplace_back(texture, 1);
	return texture;
}

void CTextureSystem::UnloadTexture(const char* texture_id)
{
	erase_if(m_pLoadedTextures, [texture_id](std::pair<std::shared_ptr<ITexture>, unsigned>& texture) -> bool
		{
			return texture.first->GetName() == texture_id && --texture.second == 0;
		});
}

void CTextureSystem::UnloadTexture(const std::shared_ptr<ITexture>& texture)
{
	if (!texture) 
		return;
	UnloadTexture(texture->GetName().c_str());
}

SpriteData_t CTextureSystem::ParseSpriteData(const char* data) const
{
	nlohmann::json json = nlohmann::json::parse(data);
	float default_framerate = json.contains("framerate") ? json["framerate"].get<float>() : 1.f;

	SpriteData_t sprite_data;
	sprite_data.texture_id = json["texture"].get<std::string>();
	sprite_data.columns = json["columns"].get<int>();
	sprite_data.rows = json["rows"].get<int>();

	for (const auto& animation : json["animations"])
	{
		SpriteData_t::AnimationData_t animation_data;
		animation_data.name = animation["name"].get<std::string>();
		animation_data.frame_rate = animation.contains("framerate") ? animation["framerate"].get<float>() : default_framerate;

		if (animation["frames"].is_array())
		{
			for (const auto& frame : animation["frames"])
			{
				animation_data.frames.push_back(frame.get<int>());
			}
		}
		else
		{
			int first = animation["frames"]["first"].get<int>();
			int last = animation["frames"]["last"].get<int>();
			int step = animation["frames"].contains("step") ? animation["frames"]["step"].get<int>() : 1;

			for (int i = first; i <= last; i += step)
			{
				animation_data.frames.push_back(i);
			}
		}

		sprite_data.animations.push_back(animation_data);
	}

	return sprite_data;
}
