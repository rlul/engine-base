#pragma once

class IGameEvent;

abstract_class IGameEventListener
{
public:
	virtual void FireGameEvent(IGameEvent* event) = 0;
};
