#include "gameclient.h"
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

CGameClient g_GameClient;
CREATE_SINGLE_SYSTEM( CGameClient, IGameClient, GAME_CLIENT_VERSION, g_GameClient )

bool CGameClient::Setup()
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	g_pEntityList->Setup();

	g_pEntityList->AddEntity(new CBasePlayer);
	auto test_entity = new CDarkMage;
	test_entity->SetPos(20, 20);
	g_pEntityList->AddEntity(test_entity);
	
	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		auto entity = g_pEntityList->GetEntity(i);
		entity->Spawn();
	}

	m_pViewport = new CGameViewport;
	m_pViewport->Setup(g_pGraphics->GetRenderer());
	m_pViewport->GetCamera()->SetScale(4);

	return true;
}

void CGameClient::Shutdown()
{
	g_pEntityList->Clear();
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

IBaseEntity* CGameClient::CreateEntity(const char* entity_name)
{
	return nullptr;
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}

ICamera* CGameClient::GetActiveCamera()
{
	return m_pViewport->GetCamera();
}
