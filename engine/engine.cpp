#include "engine.h"
#include "engine/iinputsystem.h"
#include "render/igraphics.h"
#include "core/icommandline.h"
#include "core/ifilesystem.h"
#include "game/igameclient.h"
#include "subsystem.h"
#include "common.h"
#include <SDL2/SDL.h>
#include <tmxlite/Map.hpp>
#include <thread>
#include <chrono>
#include <cmath>
#include <filesystem>

#include "tilemap.h"

CEngine g_Engine;
CREATE_SINGLE_SYSTEM( CEngine, IEngine, ENGINE_SYSTEM_VERSION, g_Engine );

bool CEngine::Setup()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	m_flPreviousTime = COM_GetTime();

	return true;
}

void CEngine::Shutdown()
{
	SDL_Quit();
}

EngineMainResult_t CEngine::Main()
{
	auto result = EngineMainResult_t::STOP;

	if (!MainLoop())
	{
		result = EngineMainResult_t::RESTART;
	}

	return result;
}

bool CEngine::GetQuitting() const
{
	return m_bQuitting;
}

void CEngine::SetQuitting(bool quit)
{
	m_bQuitting = quit;
}

float CEngine::GetFrameTime() const
{
	return m_flFrameTime;
}

bool CEngine::IsInGame() const
{
	return m_pScene;
}

bool CEngine::LoadScene(const char* name)
{
	if (m_pScene)
		UnloadScene();

	std::ostringstream map_path;
	map_path << "scenes/" << name << ".tmx";

	auto file_handle = g_pFileSystem->Open(map_path.str().c_str(), IFileSystem::OPEN_READ);

	if (!file_handle)
		return false;

	auto file_path = g_pFileSystem->GetFilePath(file_handle);
	auto file_size = g_pFileSystem->Size(file_handle) + 1;
	auto file_data = new char[file_size] { 0, };
	g_pFileSystem->Read(file_handle, file_data, file_size);
	g_pFileSystem->Close(file_handle);

	std::filesystem::path working_directory = file_path;
	working_directory.remove_filename();

	tmx::Map map;
	map.loadFromString(file_data, working_directory.string());
	delete[] file_data;

	auto scene = new CTileMap(name);

	if (!scene->Load(map))
	{
		delete scene;
		return false;
	}

	m_pScene = scene;

	return true;
}

void CEngine::UnloadScene()
{
	delete m_pScene;
	m_pScene = nullptr;
}

ITileMap* CEngine::GetCurrentScene() const
{
	return m_pScene;
}

bool CEngine::MainLoop()
{
	while (true)
	{
		if (GetQuitting())
		{
			return true;
		}
		PollEvent();
		Frame();
	}

	return false;
}

void CEngine::PollEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		g_pGraphics->ProcessEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
		{
			SetQuitting(true);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			
			break;
		}
		case SDL_KEYDOWN:
		{
			g_pInputSystem->SetKeyState(event.key.keysym.sym, true);
			break;
		}
		case SDL_KEYUP:
		{
			g_pInputSystem->SetKeyState(event.key.keysym.sym, false);
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void CEngine::Frame()
{
	m_flCurrentTime = COM_GetTime();
	float deltatime = m_flCurrentTime - m_flPreviousTime;
	m_flPreviousTime = m_flCurrentTime;
	m_flFrameTime += deltatime;

	if (!FilterTime(m_flFrameTime))
	{
		unsigned sleeptime = std::floor((m_flMinFrameTime - m_flFrameTime) * 1000000);
		std::this_thread::sleep_for(std::chrono::microseconds(sleeptime));
		return;
	}

	g_pInputSystem->Update();
	g_pGameClient->Update(m_flFrameTime);
	g_pGraphics->Frame();

	m_flFrameTime = 0.f;
}

bool CEngine::FilterTime(float deltatime)
{
	static float max_fps = [&]() -> float {
			if (!g_pCommandLine->HasParam("fps"))
				return 60.f;
			const float fps = g_pCommandLine->GetParamInt("fps");
			return (fps >= 10.f && fps <= 300.f) ? fps : 60.f;
		}();

	m_flMinFrameTime = 1.f / max_fps;

	if (deltatime < m_flMinFrameTime)
	{
		return false;
	}

	return true;
}
