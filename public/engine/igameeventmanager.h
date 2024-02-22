#pragma once
#include "engine/module.h"
#include "engine/igameevent.h"
#include "subsystem/iappsystem.h"

#define GAMEEVENTMANAGER_VERSION "GameEventManager001"

class IGameEventListener;

abstract_class IGameEventManager : public IAppSystem
{
public:
	virtual void AddListener(IGameEventListener* listener, const char* event_name) = 0;
	virtual void RemoveListener(IGameEventListener* listener, const char* event_name) = 0;

	virtual void FireGameEvent(IGameEvent* event) = 0;
};

ENGINE_API IGameEventManager* GameEventManager();
