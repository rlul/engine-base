#pragma once

abstract_class IEvent
{
public:
	virtual ~IEvent() = default;

	virtual const char* GetName() const = 0;

	virtual int GetValue(const char* name) const = 0;
	virtual void SetValue(const char* name, int value) = 0;
};
