#pragma once
#include "game/igameclient.h"

class IViewport;

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

	virtual IBaseEntity* CreateEntity(const char* entity_name) override;
	virtual IBaseEntity* GetLocalPlayer() override;
	virtual ICamera* GetActiveCamera() override;

private:
	IViewport* m_pViewport;
};
