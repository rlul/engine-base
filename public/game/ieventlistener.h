#pragma once
#include "ieventsystem.h"
#include "subsystems.h"

class IEvent;

abstract_class IEventListener
{
public:
	IEventListener()
		: m_bIsListening(false)
	{
	}

	virtual ~IEventListener() = default;

	virtual void StartListening(const char* event_name) const
	{
		if (g_pEventSystem)
		{
			g_pEventSystem->AddListener(const_cast<IEventListener*>(this), event_name);
		}
	}

	virtual void StopListening() const
	{
		if (!m_bIsListening)
			return;

		if (g_pEventSystem)
		{
			g_pEventSystem->RemoveListener(const_cast<IEventListener*>(this));
		}
	}

	virtual void FireGameEvent(IEvent* event) = 0;

private:
	bool m_bIsListening;
};
