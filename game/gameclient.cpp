#include "game/igameclient.h"
#include "subsystem.h"
#include "baseentity.h"
#include "baseplayer.h"
#include "game/ientitylist.h"

class CGameClient : public IGameClient
{
public:
	CGameClient() = default;
	virtual ~CGameClient() override = default;

	virtual bool Setup() override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return GAME_CLIENT_VERSION; }

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual bool IsInGame() override;
	IBaseEntity* GetLocalPlayer() override;

private:
	
};

CGameClient g_GameClient;
CREATE_SINGLE_SYSTEM( CGameClient, IGameClient, GAME_CLIENT_VERSION, g_GameClient )

bool CGameClient::Setup()
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	g_pEntityList->Setup();

	auto test_entity = new CBasePlayer;
	test_entity->SetPos(100, 100);
	g_pEntityList->AddEntity(test_entity);

	g_pEntityList->AddEntity(new CBasePlayer);

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->Spawn();
	}

	return true;
}

void CGameClient::Shutdown()
{
	g_pEntityList->Release();
}

void CGameClient::Update(float dt)
{
	if (!IsInGame())
	{
		return;
	}

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->Update(dt);
	}
}

void CGameClient::Render()
{
	if (!IsInGame())
	{
		return;
	}

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->GetRenderable()->Render();
	}
}

bool CGameClient::IsInGame()
{
	return true;
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}
