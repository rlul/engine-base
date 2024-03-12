#include "engine/iengine.h"
#include "render/igraphics.h"
#include "subsystem.h"
#include "common.h"
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <cmath>

#include "testeventlistener.h"
#include "core/icommandline.h"

class CEngine : public IEngine
{
public:
	CEngine() = default;
	~CEngine() override = default;

	bool Setup() override;
	void Shutdown() override;
	const char* GetSystemName() const override { return ENGINE_SYSTEM_VERSION; }

	int Main() override;
	bool GetQuitting() const override;
	void SetQuitting(bool quit) override;

private:
	virtual bool MainLoop();
	virtual void PollEvent();
	virtual void Frame();
	virtual bool FilterTime(float deltatime);

private:
	bool m_bQuitting;
	float m_flPreviousTime, m_flCurrentTime;
	float m_flFrameTime, m_flMinFrameTime;
};

CEngine g_Engine;
CREATE_SINGLE_SYSTEM( CEngine, IEngine, ENGINE_SYSTEM_VERSION, g_Engine );

bool CEngine::Setup()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}

	m_flPreviousTime = COM_GetTime();

	g_pEventSystem->AddListener(new CTestEventListener, "mousedown");

	return true;
}

void CEngine::Shutdown()
{
	SDL_Quit();
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

bool CEngine::GetQuitting() const
{
	return m_bQuitting;
}

void CEngine::SetQuitting(bool quit)
{
	m_bQuitting = quit;
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
			int mouse_x, mouse_y;
			IEvent* mouse_event = g_pEventSystem->CreateGameEvent("mousedown");

			SDL_GetMouseState(&mouse_x, &mouse_y);
			mouse_event->SetValue("mouse_x", mouse_x);
			mouse_event->SetValue("mouse_y", mouse_y);
			g_pEventSystem->FireGameEvent(mouse_event);

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
