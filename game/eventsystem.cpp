#include "eventsystem.h"
#include "subsystems.h"
#include "subsystem.h"
#include <ranges>

CEventSystem g_EventSystem;
CREATE_SINGLE_SYSTEM(CEventSystem, IEventSystem, EVENT_SYSTEM_VERSION, g_EventSystem);

CEvent::CEvent(const char* name)
	: m_pszName(name)
{

}

const char* CEvent::GetName() const
{
	return m_pszName;
}

int CEvent::GetValue(const char* name) const
{
	return m_mapValues.at(name);
}

void CEvent::SetValue(const char* name, int value)
{
	m_mapValues[name] = value;
}

void CEventSystem::Shutdown()
{
	m_mapEventListeners.clear();
}

void CEventSystem::AddListener(IEventListener* listener, const char* event_name)
{
	m_mapEventListeners[event_name].push_back(listener);
}

void CEventSystem::RemoveListener(IEventListener* listener, const char* event_name)
{
	std::erase(m_mapEventListeners[event_name], listener);
}

void CEventSystem::RemoveListener(IEventListener* listener)
{
	for (auto& listeners : m_mapEventListeners | std::views::values)
	{
		std::erase(listeners, listener);
	}
}

IEvent* CEventSystem::CreateGameEvent(const char* event_name)
{
	if (!m_mapEventListeners.contains(event_name))
	{
		printf("Tried to create an event (%s) with no registered listeners.\n", event_name);
		return nullptr;
	}

	return new CEvent(event_name);
}

void CEventSystem::FireGameEvent(IEvent* event)
{
	if (event == nullptr)
	{
		return;
	}

	const std::string& event_type = event->GetName();

	if (m_mapEventListeners.contains(event_type))
	{
		for (IEventListener* listener : m_mapEventListeners[event_type])
		{
			listener->FireGameEvent(event);
		}
	}

	delete event;
}
