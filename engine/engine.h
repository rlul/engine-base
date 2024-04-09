#pragma once
#include "engine/iengine.h"

class CEngine : public IEngine
{
public:
	CEngine() = default;
	virtual ~CEngine() override = default;

	virtual bool Setup() override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return ENGINE_SYSTEM_VERSION; }

	virtual int Main() override;
	virtual bool GetQuitting() const override;
	virtual void SetQuitting(bool quit) override;

	virtual float GetFrameTime() const override;

	virtual bool IsInGame() const override;
	virtual bool LoadScene(const char* name) override;
	virtual void UnloadScene() override;
	virtual ITileMap* GetScene() const override;

private:
	virtual bool MainLoop();
	virtual void PollEvent();
	virtual void Frame();
	virtual bool FilterTime(float deltatime);

private:
	bool m_bQuitting;
	float m_flPreviousTime, m_flCurrentTime;
	float m_flFrameTime, m_flMinFrameTime;

	ITileMap* m_pScene;
};