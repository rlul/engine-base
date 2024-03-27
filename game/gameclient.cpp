#include "game/igameclient.h"
#include "subsystem.h"
#include "baseplayer.h"

class CGameClient : public IGameClient
{
public:
	CGameClient() = default;
	~CGameClient() override = default;

	bool Setup() override;
	void Shutdown() override;
	const char* GetSystemName() const override { return GAME_CLIENT_VERSION; }

	IBaseEntity* GetLocalPlayer() override;

private:
	
};

CGameClient g_GameClient;
CREATE_SINGLE_SYSTEM( CGameClient, IGameClient, GAME_CLIENT_VERSION, g_GameClient )

bool CGameClient::Setup()
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	return true;
}

void CGameClient::Shutdown()
{
	
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}
