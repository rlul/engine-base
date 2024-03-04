#pragma once
#include "engine/iengine.h"
#include "engine/ievent.h"
#include "engine/ieventlistener.h"
#include "engine/ieventsystem.h"
#include "subsystems.h"
#include <cstring>

class CTestEventListener : public IEventListener
{
public:
	CTestEventListener() = default;
	~CTestEventListener() override = default;

	void FireGameEvent(IEvent* event) override
	{
		if (strcmp(event->GetName(), "mousedown") == 0)
		{
			int mouse_x, mouse_y;
			mouse_x = event->GetValue("mouse_x");
			mouse_y = event->GetValue("mouse_y");
			if (mouse_x < 100 && mouse_y < 100)
			{
				printf("yes!");
				g_pEventSystem->RemoveListener(this, "mousedown");
			}
			else
			{
				printf("no!");

			}
			printf(" (%d, %d)\n", mouse_x, mouse_y);
		}
	}
};
