#pragma once
#include "engine/igameeventlistener.h"
#include "engine/igameevent.h"
#include "engine/igameeventmanager.h"
#include "subsystem/iappsystemgroup.h"
#include "engine/iengine.h"
#include <cstring>

class CTestEventListener : public IGameEventListener 
{
public:
	CTestEventListener() = default;
	~CTestEventListener() override = default;

	void FireGameEvent(IGameEvent* event) override
	{
		if (strcmp(event->GetName(), "mousedown") == 0)
		{
			int mouse_x, mouse_y;
			mouse_x = event->GetValue("mouse_x");
			mouse_y = event->GetValue("mouse_y");
			if (mouse_x < 100 && mouse_y < 100)
			{
				printf("yes!");
				((IGameEventManager*)GetAppSystem(GAMEEVENTMANAGER_VERSION))->RemoveListener(this, "mousedown");
			}
			else
			{
				printf("no!");

			}
			printf(" (%d, %d)\n", mouse_x, mouse_y);
		}
	}
};
