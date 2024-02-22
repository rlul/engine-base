#include "engine/igameeventmanager.h"
#include "engine/igameeventlistener.h"
#include "subsystem/iappsystem.h"
#include <string>
#include <vector>
#include <unordered_map>

class CGameEvent : public IGameEvent
{
public:
	CGameEvent(const char* name);
	~CGameEvent() override;

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

CGameEvent::~CGameEvent()
{
	delete m_pszName;
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


class CGameEventManager : public IGameEventManager
{
	APPSYSTEM_OBJECT(GAMEEVENTMANAGER_VERSION)
public:
	CGameEventManager();
	~CGameEventManager() override = default;

	void AddListener(IGameEventListener* listener, const char* event_name) override;
	void RemoveListener(IGameEventListener* listener, const char* event_name) override;

	IGameEvent* CreateGameEvent(const char* event_name) override;
	void FireGameEvent(IGameEvent* event) override;


private:
	std::unordered_map<std::string, std::vector<IGameEventListener*>> m_mapEventListeners;

};

bool CGameEventManager::Setup()
{
	m_bIsSetup = true;

	return true;
}

void CGameEventManager::Shutdown()
{
	m_bIsSetup = false;
}

CGameEventManager::CGameEventManager()
	: m_bIsSetup(false)
{
}

void CGameEventManager::AddListener(IGameEventListener* listener, const char* event_name)
{
	m_mapEventListeners[event_name].push_back(listener);
}

void CGameEventManager::RemoveListener(IGameEventListener* listener, const char* event_name)
{
	std::erase(m_mapEventListeners[event_name], listener);
}

IGameEvent* CGameEventManager::CreateGameEvent(const char* event_name)
{
	if (!m_mapEventListeners.contains(event_name))
	{
		printf("Tried to create an event (%s) with no registered listeners.\n", event_name);
		return nullptr;
	}

	return new CGameEvent(event_name);
}

void CGameEventManager::FireGameEvent(IGameEvent* event)
{
	if (event == nullptr)
	{
		return;
	}

	const std::string& event_type = event->GetName();

	if (m_mapEventListeners.contains(event_type)) 
	{
		for (IGameEventListener* listener : m_mapEventListeners[event_type]) 
		{
			listener->FireGameEvent(event);
		}
	}
}

CGameEventManager g_GameEventManager;
IGameEventManager* GameEventManager()
{
	return &g_GameEventManager;
}