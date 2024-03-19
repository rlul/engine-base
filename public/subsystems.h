#pragma once

abstract_class IAppSystem
{
public:
	virtual void Shutdown() = 0;
	virtual const char* GetSystemName() const = 0;
};

typedef IAppSystem* (*GetSystemFn)(const char* name);

#define DECLARE_SYSTEM( system, name )	\
	class system;	\
	extern system* name	\

DECLARE_SYSTEM( IEngine, g_pEngine );
DECLARE_SYSTEM( IEventSystem, g_pEventSystem );
DECLARE_SYSTEM( IGraphics, g_pGraphics );
DECLARE_SYSTEM( ISpriteSystem, g_pSpriteSystem );
DECLARE_SYSTEM( ICommandLine, g_pCommandLine );
DECLARE_SYSTEM( IFileSystem, g_pFileSystem );

void RegisterSystems(GetSystemFn* factory, const char* name, IAppSystem** system);
void ConnectSystems(GetSystemFn* factory_list, unsigned factory_count);
