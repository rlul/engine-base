#pragma once

abstract_class IGameEvent
{
public:
	virtual const char* GetName() const = 0;
	virtual int GetValue() const = 0;
};