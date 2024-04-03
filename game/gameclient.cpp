#include "game/igameclient.h"
#include "game/ientitylist.h"
#include "game/icamera.h"
#include "render/igraphics.h"
#include "subsystem.h"
#include "staticcamera.h"
#include "baseentity.h"
#include "baseplayer.h"
#include "ent_darkmage.h"

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
	virtual IBaseEntity* GetLocalPlayer() override;
	virtual ICamera* GetActiveCamera() override { return m_pActiveCamera; }

private:
	ICamera* m_pActiveCamera;
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

	m_pActiveCamera = new CStaticCamera;
	m_pActiveCamera->Setup(g_pGraphics->GetRenderer());
	m_pActiveCamera->SetPos(0, 0);
	m_pActiveCamera->SetZoom(1.f);
	m_pActiveCamera->SetRotation(0.f);
	m_pActiveCamera->SetViewport(0, 0);

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

	m_pActiveCamera->Update(dt);
}

void CGameClient::Render()
{
	if (!IsInGame())
	{
		return;
	}

	m_pActiveCamera->Render();
}

bool CGameClient::IsInGame()
{
	return true;
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}
