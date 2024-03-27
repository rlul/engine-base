#pragma once
#include "subsystems.h"

#define GAME_CLIENT_VERSION "GameClient001"

class IBaseEntity;

abstract_class IGameClient : public IAppSystem
{
public:
	virtual ~IGameClient() = default;

	virtual bool Setup() = 0;

	virtual IBaseEntity* GetLocalPlayer() = 0;
};
