#include "spritesystem.h"

#include <iostream>

#include "render/ispritesystem.h"
#include "core/ifilesystem.h"
#include "subsystem.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <sstream>

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
	char* file_buf;
	nlohmann::json json_data;
	SpriteData_t sprite_data;

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
	file_buf = new char[file_size] { 0, };
	g_pFileSystem->Read(file, file_buf, file_size);

	printf("Sprite %s:\n%s\n", filename, file_buf);

	json_data = nlohmann::json::parse(file_buf);

	delete[] file_buf;
	g_pFileSystem->Close(file);

	sprite_data = ParseSpriteData(json_data);

	if (!ValidateSpriteData(sprite_data))
	{
		printf("Failed to validate sprite data for %s\n", filename);
		return nullptr;
	}

	SDL_Texture* texture = LoadTexture(sprite_data.texture_path);

	if (!texture)
	{
		return nullptr;
	}

	CSprite* sprite = new CSprite;
	sprite->m_pszPath = filename;
	sprite->m_pTexture = texture;
	sprite->m_nColumns = sprite_data.columns;
	sprite->m_nRows = sprite_data.rows;
	sprite->m_nAnimationCount = sprite_data.animation_count;
	sprite->m_pAnimations = new CSprite::Animation_t[sprite_data.animation_count];

	for (int i = 0; i < sprite_data.animation_count; ++i)
	{
		strcpy(sprite->m_pAnimations[i].name, sprite_data.animations[i].name);
		sprite->m_pAnimations[i].frame_rate = sprite_data.animations[i].frame_rate;
		sprite->m_pAnimations[i].frame_count = sprite_data.animations[i].frame_count;

		for (int j = 0; j < sprite_data.animations[i].frame_count; ++j)
		{
			sprite->m_pAnimations[i].frames[j] = sprite_data.animations[i].frames[j];
		}
	}

	//sprite->m_flFrameRate = sprite_data.frame_rate;
	//sprite->m_pFrames = new int[sprite_data.frame_count];
	//for (int i = 0; i < sprite_data.frame_count; i++)
	//{
	//	sprite->m_pFrames[i] = sprite_data.frames[i];
	//}
	//sprite->m_nFrameCount = sprite_data.frame_count;

	SDL_QueryTexture(texture, NULL, NULL, &sprite->m_iFrameWidth, &sprite->m_iFrameHeight);
	sprite->m_iFrameWidth /= sprite_data.columns;
	sprite->m_iFrameHeight /= sprite_data.rows;

	m_LoadedSprites.push_back(sprite);

	return sprite;
}

void CSpriteSystem::UnloadSprite(ISprite* sprite)
{
	// TODO: check if spite's texture is still in use by other sprites and unload it if not
}

bool CSpriteSystem::DrawSprite(ISprite* sprite, int x, int y, float scale)
{
	return DrawSpriteEx(sprite, 0, 0, x, y, scale, scale);
}

bool CSpriteSystem::DrawSpriteEx(ISprite* sprite, int animation_index, int frame_index, int x, int y, float scale_x, float scale_y)
{
	SDL_Rect src, dst;
	int columns, rows;
	int frame_width, frame_height;
	int frame_count, frame;

	if (!sprite)
	{
		return false;
	}
	sprite->GetSpriteSize(columns, rows);
	sprite->GetFrameSize(frame_width, frame_height);
	frame_count = sprite->GetFrameCount(animation_index);
	frame = sprite->GetFrame(frame_index, animation_index);

	if (frame < 0)
	{
		return false;
	}

	src = { (frame % columns) * frame_width, (frame / columns) * frame_height, frame_width, frame_height };
	dst = { x, y, int(frame_width * scale_x), int(frame_height * scale_y) };

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

CSpriteSystem::SpriteData_t CSpriteSystem::ParseSpriteData(nlohmann::json& json_data)
{
	SpriteData_t data;
	float default_framerate;

	strcpy(data.texture_path, static_cast<std::string>(json_data["texture"]).c_str());
	data.columns = json_data["columns"];
	data.rows = json_data["rows"];
	default_framerate = json_data.contains("framerate") ? (float)json_data["framerate"] : 1.f;
	data.animation_count = json_data["animations"].size();

	if (data.animation_count > 32)
	{
		// TODO: log error
		data.animation_count = 32;
	}

	for (int i = 0; i < data.animation_count; ++i)
	{
		auto& animation = json_data["animations"][i];
		strcpy(data.animations[i].name, static_cast<std::string>(animation["name"]).c_str());
		data.animations[i].frame_rate = animation.contains("framerate") ? (float)animation["framerate"] : default_framerate;

		if (animation["frames"].is_array())
		{
			data.animations[i].frame_count = animation["frames"].size();

			for (int j = 0; j < data.animations[i].frame_count; ++j)
			{
				data.animations[i].frames[j] = animation["frames"][j];
			}
		}
		else
		{
			int first = animation["frames"]["first"];
			int last = animation["frames"]["last"];
			int step = animation.contains("step") ? static_cast<int>(animation["frames"]["step"]) : 1;

			data.animations[i].frame_count = (last - first) / step + 1;

			for (int j = 0; j < data.animations[i].frame_count; ++j)
			{
				data.animations[i].frames[j] = first + j * step;
			}
		}
	}

	//data.frame_rate = json_data["frame_rate"];
	//if (json_data["frames"].is_array())
	//{
	//	int i = 0;
	//	for (auto& frame : json_data["frames"])
	//	{
	//		data.frames[i++] = frame;
	//	}
	//	data.frame_count = i;
	//}
	//else
	//{
	//	int first = json_data["frames"]["first"];
	//	int last = json_data["frames"]["last"];
	//	int step = json_data["frames"].contains("step") ? static_cast<int>(json_data["frames"]["step"]) : 1;

	//	data.frame_count = (last - first) / step + 1;
	//	
	//	for (int i = 0; i < data.frame_count; ++i)
	//	{
	//		data.frames[i] = first + i * step;
	//	}
	//}


	return data;
}

bool CSpriteSystem::ValidateSpriteData(SpriteData_t& data)
{
	// TODO

	return true;
}
