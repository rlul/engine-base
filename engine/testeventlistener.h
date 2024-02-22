#pragma once
#include "engine/igameeventlistener.h"
#include "engine/igameevent.h"
#include "engine/igameeventmanager.h"
#include "subsystem/iappsystemgroup.h"
#include "engine/iengine.h"
#include <cstring>

class CMouseDownEvent : public IGameEvent
{
public:
	CMouseDownEvent() = default;
	~CMouseDownEvent() = default;

	const char* GetName() const override { return "mousedown"; }
	int GetValue() const override { return 0; }

};

class CTestEventListener : public IGameEventListener 
{
public:
	CTestEventListener() = default;
	~CTestEventListener() = default;

	void FireGameEvent(IGameEvent* event) override 
	{
		if (strcmp(event->GetName(), "mousedown") == 0)
		{
			printf("govno\n");
			((IGameEventManager*)GetAppSystem(GAMEEVENTMANAGER_VERSION))->RemoveListener(this, "mousedown");
		}
	}
};
