#pragma once
#include "subsystems.h"

#define ENGINE_SYSTEM_VERSION "Engine001"

class ITileMap;

enum class EngineMainResult_t
{
	STOP,
	RESTART
};

abstract_class IEngine : public IAppSystem
{
public:
	virtual ~IEngine() = default;

	virtual bool Setup() = 0;

	virtual EngineMainResult_t Main() = 0;
	virtual bool GetQuitting() const = 0;
	virtual void SetQuitting(bool quit) = 0;

	virtual float GetFrameTime() const = 0;

	virtual bool IsInGame() const = 0;
	virtual bool LoadScene(const char* name) = 0;
	virtual void UnloadScene() = 0;
	virtual ITileMap* GetCurrentScene() const = 0;
};
