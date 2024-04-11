#include "gameclient.h"
#include "game/ientitylist.h"
#include "game/icamera.h"
#include "game/iviewport.h"
#include "render/igraphics.h"
#include "engine/iengine.h"
#include "engine/itilemap.h"
#include "subsystem.h"
#include "baseentity.h"
#include "baseplayer.h"
#include "gameviewport.h"

CGameClient g_GameClient;
CREATE_SINGLE_SYSTEM( CGameClient, IGameClient, GAME_CLIENT_VERSION, g_GameClient )

bool CGameClient::Setup()
{
	auto factory = GetGameFactory();
	ConnectSystems(&factory, 1);

	LoadLevel("testmap");

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

	g_pEngine->GetCurrentScene()->Render();

	m_pViewport->Render();
}

bool CGameClient::LoadLevel(const char* map_name)
{
	if (g_pEngine->IsInGame())
		UnloadLevel();

	if (!g_pEntityList->Setup())
	{
		printf("Failed to setup entity list!\n");
		return false;
	}

	if (!g_pEngine->LoadScene(map_name))
	{
		printf("Failed to load scene: %s\n", map_name);
		return false;
	}

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
		g_pEntityList->GetEntity(i)->Spawn();

	m_pViewport = new CGameViewport;
	m_pViewport->Setup(g_pGraphics->GetRenderer());
	m_pViewport->GetCamera()->SetScale(4);

	return true;
}

void CGameClient::UnloadLevel()
{
	if (m_pViewport)
	{
		m_pViewport->Shutdown();
		delete m_pViewport;
		m_pViewport = nullptr;
	}

	g_pEntityList->Clear();
	g_pEngine->UnloadScene();
}

IBaseEntity* CGameClient::CreateEntity(const char* entity_name)
{
	auto factory = CEntityRegistry::GetEntityFactory(entity_name);
	if (!factory)
	{
		printf("Tried to create an unregistered entity: %s\n", entity_name);
		return nullptr;
	}

	return factory();
}

IBaseEntity* CGameClient::GetLocalPlayer()
{
	return CBasePlayer::GetLocalPlayer();
}

ICamera* CGameClient::GetActiveCamera()
{
	if (!g_pEngine->IsInGame())
		return nullptr;

	return m_pViewport->GetCamera();
}
