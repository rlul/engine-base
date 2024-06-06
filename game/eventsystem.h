#pragma once
#include "game/ievent.h"
#include "game/ieventsystem.h"
#include "game/ieventlistener.h"
#include <unordered_map>
#include <vector>
#include <string>

class CEvent : public IEvent
{
public:
	CEvent(const char* name);
	~CEvent() override = default;

	const char* GetName() const override;

	int GetValue(const char* name) const override;
	void SetValue(const char* name, int value) override;

private:
	const char* m_pszName;
	std::unordered_map<std::string, int> m_mapValues;
};

class CEventSystem : public IEventSystem
{
public:
	CEventSystem() = default;
	~CEventSystem() override = default;

	void Shutdown() override;
	const char* GetSystemName() const override { return EVENT_SYSTEM_VERSION; }

	void AddListener(IEventListener* listener, const char* event_name) override;
	void RemoveListener(IEventListener* listener, const char* event_name) override;
	void RemoveListener(IEventListener* listener) override;

	IEvent* CreateGameEvent(const char* event_name) override;
	void FireGameEvent(IEvent* event) override;

private:
	std::unordered_map<std::string, std::vector<IEventListener*>> m_mapEventListeners;
};
