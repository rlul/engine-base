#pragma once

class CEngine 
{
public:
	CEngine();
	~CEngine();

	bool Setup();
	void Shutdown();
	int Main();

	bool GetQuitting() const { return m_bIsQuitting; }
	void SetQuitting(bool quit) { m_bIsQuitting = quit; }

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

CEngine* Engine();
