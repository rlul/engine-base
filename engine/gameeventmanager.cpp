#include "engine/igameeventmanager.h"
#include "engine/igameeventlistener.h"
#include "subsystem/iappsystem.h"
#include <string>
#include <vector>
#include <unordered_map>

class CGameEventManager : public IGameEventManager
{
	APPSYSTEM_OBJECT(GAMEEVENTMANAGER_VERSION)
public:
	CGameEventManager();
	~CGameEventManager() = default;

	void AddListener(IGameEventListener* listener, const char* event_name) override;
	void RemoveListener(IGameEventListener* listener, const char* event_name) override;

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

void CGameEventManager::FireGameEvent(IGameEvent* event)
{
	const std::string& eventType = event->GetName();

	if (m_mapEventListeners.contains(eventType)) 
	{
		for (IGameEventListener* listener : m_mapEventListeners[eventType]) 
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