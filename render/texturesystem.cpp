#include "texturesystem.h"
#include "sprite.h"
#include "texture.h"
#include "core/ifilesystem.h"
#include "subsystem.h"
#include "subsystems.h"
#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>
#include <SDL_image.h>
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
	
}

void CTextureSystem::DrawSprite(const std::shared_ptr<ISprite>& sprite, int animation_index, int frame_index, int x1, int y1, int x2, int y2, float rotation)
{
	SDL_Rect src_rect, dest_rect;
	int columns, rows;
	int frame_width, frame_height;
	int frame;

	if (!sprite) return;

	sprite->GetSpriteSize(columns, rows);
	sprite->GetFrameSize(frame_width, frame_height);
	frame = sprite->GetFrame(frame_index, animation_index);

	if (frame < 0) return;

	src_rect = { (frame % columns) * frame_width, (frame / columns) * frame_height, frame_width, frame_height };
	dest_rect = { x1, y1, x2 - x1, y2 - y1 };

	SDL_RenderCopyEx(m_pRenderer, sprite->GetTexture()->GetTexture(), &src_rect, &dest_rect, rotation, NULL, SDL_FLIP_NONE);
}

std::shared_ptr<ISprite> CTextureSystem::LoadSprite(const char* sprite_id)
{
	for (auto& loaded_sprite : m_pLoadedSprites)
	{
		if (strcmp(loaded_sprite.first->GetName(), sprite_id) == 0)
		{
			++loaded_sprite.second;
			return loaded_sprite.first;
		}
	}

	std::ostringstream sprite_path;
	sprite_path << "sprites/" << sprite_id << ".json";

	auto file = g_pFileSystem->Open(sprite_path.str().c_str(), IFileSystem::OPEN_READ);
	auto file_size = g_pFileSystem->Size(file) + 1;
	auto file_data = new char[file_size] { 0, };
	g_pFileSystem->Read(file, file_data, file_size);

	auto sprite_data = ParseSpriteData(file_data);
	delete[] file_data;
	g_pFileSystem->Close(file);

	auto texture = LoadTexture(sprite_data.texture_id.c_str());
	if (!texture)
	{
		return nullptr;
	}

	auto sprite = std::make_shared<CSprite>(sprite_id, texture, sprite_data);

	m_pLoadedSprites.emplace_back(sprite, 1);
	return sprite;
}

void CTextureSystem::UnloadSprite(const char* sprite_id)
{
}

void CTextureSystem::UnloadSprite(const std::shared_ptr<ISprite>& sprite)
{
}

std::shared_ptr<ITexture> CTextureSystem::LoadTexture(const char* texture_id)
{
	for (auto& loaded_texture : m_pLoadedTextures)
	{
		if (strcmp(loaded_texture.first->GetName(), texture_id) == 0)
		{
			++loaded_texture.second;
			return loaded_texture.first;
		}
	}

	std::ostringstream texture_path;
	texture_path << "textures/" << texture_id << ".png";

	auto file_handle = g_pFileSystem->Open(texture_path.str().c_str(), IFileSystem::OPEN_READ);
	auto file_size = g_pFileSystem->Size(file_handle);
	auto file_data = new char[file_size] { 0, };
	g_pFileSystem->Read(file_handle, file_data, file_size);

	auto rw = SDL_RWFromMem(file_data, file_size);
	auto surface = IMG_Load_RW(rw, 1);

	delete[] file_data;
	g_pFileSystem->Close(file_handle);

	if (!surface)
	{
		printf("Failed to load surface %s\n", texture_id);
		return nullptr;
	}

	auto texure_handle = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	if (!texure_handle)
	{
		printf("Failed to create texture from surface %s\n", texture_id);
		return nullptr;
	}

	auto texture = std::make_shared<CTexture>(texture_id, texure_handle);
	if (!texture)
	{
		return nullptr;
	}

	m_pLoadedTextures.emplace_back(texture, 1);
	return texture;
}

void CTextureSystem::UnloadTexture(const char* texture_id)
{
}

void CTextureSystem::UnloadTexture(const std::shared_ptr<ITexture>& texture)
{
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
