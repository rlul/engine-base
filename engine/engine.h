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

private:
	bool m_bIsQuitting;

};

CEngine* Engine();
