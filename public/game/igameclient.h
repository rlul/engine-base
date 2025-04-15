#pragma once
#include "subsystems.h"

#define GAME_CLIENT_VERSION "GameClient001"

class IBaseEntity;
class ICamera;

abstract_class IGameClient : public IAppSystem
{
public:
	virtual ~IGameClient() = default;

	virtual bool Setup() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual bool LoadLevel(const char* map_name) = 0;
	virtual void UnloadLevel() = 0;

	virtual IBaseEntity* CreateEntity(const char* entity_name) = 0;
	virtual IBaseEntity* GetLocalPlayer() = 0;
	virtual ICamera* GetActiveCamera() = 0;
};
