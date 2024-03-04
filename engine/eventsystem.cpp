#include "engine/ievent.h"
#include "engine/ieventsystem.h"
#include "engine/ieventlistener.h"
#include "subsystems.h"
#include <string>
#include <vector>
#include <unordered_map>

#include "subsystem.h"

class CGameEvent : public IEvent
{
public:
	CGameEvent(const char* name);
	~CGameEvent() override = default;

	const char* GetName() const override;

	int GetValue(const char* name) const override;
	void SetValue(const char* name, int value) override;

private:
	const char* m_pszName;
	std::unordered_map<std::string, int> m_mapValues;
};

CGameEvent::CGameEvent(const char* name)
	: m_pszName(name)
{

}

const char* CGameEvent::GetName() const
{
	return m_pszName;
}

int CGameEvent::GetValue(const char* name) const
{
	return m_mapValues.at(name);
}

void CGameEvent::SetValue(const char* name, int value)
{
	m_mapValues[name] = value;
}


class CEventSystem : public IEventSystem
{
public:
	CEventSystem() = default;
	~CEventSystem() override = default;

	void Shutdown() override;
	const char* GetSystemName() const override { return EVENT_SYSTEM_VERSION; }

	void AddListener(IEventListener* listener, const char* event_name) override;
	void RemoveListener(IEventListener* listener, const char* event_name) override;

	IEvent* CreateGameEvent(const char* event_name) override;
	void FireGameEvent(IEvent* event) override;


private:
	std::unordered_map<std::string, std::vector<IEventListener*>> m_mapEventListeners;

};

CEventSystem g_EventSystem;
CREATE_SINGLE_SYSTEM( CEventSystem, IEventSystem, EVENT_SYSTEM_VERSION, g_EventSystem );

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

IEvent* CEventSystem::CreateGameEvent(const char* event_name)
{
	if (!m_mapEventListeners.contains(event_name))
	{
		printf("Tried to create an event (%s) with no registered listeners.\n", event_name);
		return nullptr;
	}

	return new CGameEvent(event_name);
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
