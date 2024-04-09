#include "followcamera.h"
#include "subsystems.h"
#include "game/igameclient.h"
#include "game/ibaseentity.h"

CFollowCamera::CFollowCamera()
	: CStaticCamera()
{
}

CFollowCamera::~CFollowCamera()
{
	delete m_pRenderView;
}

void CFollowCamera::Update(float dt)
{
	CStaticCamera::Update(dt);

	IBaseEntity* player = g_pGameClient->GetLocalPlayer();
	SetPos(player->GetPos());
}
