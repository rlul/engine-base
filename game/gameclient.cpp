#include "game/igameclient.h"
#include "game/ientitylist.h"
#include "game/icamera.h"
#include "game/iviewport.h"
#include "render/igraphics.h"
#include "subsystem.h"
#include "baseentity.h"
#include "baseplayer.h"
#include "ent_darkmage.h"
#include "gameviewport.h"
#include "engine/iengine.h"

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

	virtual IBaseEntity* GetLocalPlayer() override;
	virtual ICamera* GetActiveCamera() override { return m_pViewport->GetCamera(); }

private:
	IViewport* m_pViewport;
};

CGameClient g_GameClient;
CREATE_SINGLE_SYSTEM( CGameClient, IGameClient, GAME_CLIENT_VERSION, g_GameClient )

bool CGameClient::Setup()
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	g_pEntityList->Setup();

	g_pEntityList->AddEntity(new CBasePlayer);
	auto test_entity = new CDarkMage;
	test_entity->SetPos(100, 100);
	g_pEntityList->AddEntity(test_entity);

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->Spawn();
	}

	m_pViewport = new CGameViewport;
	m_pViewport->Setup(g_pGraphics->GetRenderer());

	return true;
}

void CGameClient::Shutdown()
{
	g_pEntityList->Release();
}

void CGameClient::Update(float dt)
{
	if (!g_pEngine->IsInGame())
	{
		return;
	}

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->Update(dt);
	}

	m_pViewport->Update(dt);
}

void CGameClient::Render()
{
	if (!g_pEngine->IsInGame())
	{
		return;
	}

	m_pViewport->Render();
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}
