#pragma once
#include "common.h"
#include "subsystems.h"

typedef IAppSystem* (*CreateSystemFn)();

class SystemRegistration
{
public:
	SystemRegistration(CreateSystemFn fn, const char* name);

public:
	CreateSystemFn m_fnFactory;
	const char* m_pszName;
	SystemRegistration* m_pNext;
};

DLL_EXPORT IAppSystem* GetSystem(const char* name);
GetSystemFn GetModuleFactory(const char* module_name);
GetSystemFn GetGameFactory();

#define CREATE_SINGLE_SYSTEM( class, interface, version, var )	\
	static SystemRegistration __Register##class##interface( []() -> IAppSystem* {	\
			return &(var);	\
		}, version );	\
