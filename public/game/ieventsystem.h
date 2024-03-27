#pragma once
#include "subsystems.h"

#define EVENT_SYSTEM_VERSION "EventSystem001"

class IEvent;
class IEventListener;

abstract_class IEventSystem : public IAppSystem
{
public:
	virtual ~IEventSystem() = default;

	virtual void AddListener(IEventListener* listener, const char* event_name) = 0;
	virtual void RemoveListener(IEventListener* listener, const char* event_name) = 0;
	virtual void RemoveListener(IEventListener* listener) = 0;

	virtual IEvent* CreateGameEvent(const char* event_name) = 0;
	virtual void FireGameEvent(IEvent* event) = 0;
};


