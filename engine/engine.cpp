#include "common.h"
#include "engine/iengine.h"
#include "engine/igameeventmanager.h"
#include "render/igraphics.h"
#include "subsystem/iappsystemgroup.h"
#include <SDL3/SDL.h>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cmath>

#include "testeventlistener.h"

IGameEventManager* game_event_manager = nullptr;

class CEngine : public IEngine
{
	APPSYSTEM_OBJECT(ENGINE_VERSION)

public:
	CEngine();
	~CEngine() override = default;

	int Main() override;
	bool GetQuitting() const override { return m_bIsQuitting; }
	void SetQuitting(bool quit) override { m_bIsQuitting = quit; }

private:
	bool MainLoop();
	void PollEvent();
	void Frame();
	bool FilterTime(float deltatime);

private:
	bool m_bIsQuitting;
	float m_flPreviousTime, m_flCurrentTime;
	float m_flFrameTime, m_flMinFrameTime;
};

CEngine g_Engine;
IEngine* Engine()
{
	return &g_Engine;
}

CEngine::CEngine()
	: m_bIsSetup(false), m_bIsQuitting(false), m_flPreviousTime(0), m_flCurrentTime(0), m_flFrameTime(0),
	  m_flMinFrameTime(0)
{
}

bool CEngine::Setup()
{
	m_flPreviousTime = COM_GetTime();
	printf("Game Path: %s\n", COM_GetGameDir().c_str());

	game_event_manager = (IGameEventManager*)GetAppSystem(GAMEEVENTMANAGER_VERSION);
	game_event_manager->AddListener(new CTestEventListener, "mousedown");

	m_bIsSetup = true;

	return true;
}

void CEngine::Shutdown()
{
	m_bIsSetup = false;
}

int CEngine::Main()
{
	int result = 0;	// stop

	if (!MainLoop())
	{
		result = 1;	// restart
	}

	return result;
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
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
		{
			SetQuitting(true);
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			CMouseDownEvent mouse_down_event;
			game_event_manager->FireGameEvent(&mouse_down_event);
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

	{
		char buf[32];
		static float frames_per_second = 0.f, total_time = 0.f;

		++frames_per_second;
		total_time += m_flFrameTime;

		sprintf(buf, "FPS: %f", frames_per_second / total_time);
		SDL_SetWindowTitle(SDL_GL_GetCurrentWindow(), buf);

		if (total_time > 1.f)
			frames_per_second = total_time = 0.f;
	}

	Graphics()->Frame();

	m_flFrameTime = 0.f;
}

bool CEngine::FilterTime(float deltatime)
{
	float max_fps = 60.f;
	m_flMinFrameTime = 1.f / max_fps;

	if (deltatime < m_flMinFrameTime)
	{
		return false;
	}

	return true;
}
