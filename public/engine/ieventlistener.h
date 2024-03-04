#pragma once

class IEvent;

abstract_class IEventListener
{
public:
	virtual ~IEventListener() = default;

	virtual void FireGameEvent(IEvent* event) = 0;
};
