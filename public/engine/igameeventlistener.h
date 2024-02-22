#pragma once

class IGameEvent;

abstract_class IGameEventListener
{
public:
	virtual ~IGameEventListener() = default;

	virtual void FireGameEvent(IGameEvent* event) = 0;
};
