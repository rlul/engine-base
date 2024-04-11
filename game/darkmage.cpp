#include "darkmage.h"
#include "subsystems.h"
#include "render/itexturesystem.h"

REGISTER_ENTITY( "ent_darkmage", CDarkMage )

CDarkMage::CDarkMage()
	: CBaseAnimated()
{
	m_pSprite = g_pTextureSystem->LoadSprite("entity/darkmage");
	SetCurrentAnimation("idle");
	SetScale(1);
}

CDarkMage::~CDarkMage()
{
	g_pTextureSystem->UnloadSprite(m_pSprite);
	CBaseAnimated::~CBaseAnimated();
}

void CDarkMage::Spawn()
{
	CBaseAnimated::Spawn();
}

void CDarkMage::Update(float dt)
{
	CBaseAnimated::Update(dt);

	// Repeatedly walk in each direction for 1 second
	MoveInfo_t move_info{};
	m_iWalkDirection = int(m_flSpawnTime * 1) % 4;
	switch (m_iWalkDirection)
	{
	case 0:
		move_info.forwardmove = 1;
		move_info.viewdirection = ViewDirection_t::Up;
		break;
	case 1:
		move_info.sidemove = 1;
		move_info.viewdirection = ViewDirection_t::Right;
		break;
	case 2:
		move_info.forwardmove = -1;
		move_info.viewdirection = ViewDirection_t::Down;
		break;
	case 3:
		move_info.sidemove = -1;
		move_info.viewdirection = ViewDirection_t::Left;
		break;
	}
	MakeMove(move_info);

	CheckAnimationEvents();
}

void CDarkMage::Render()
{
	CBaseAnimated::Render();
}

void CDarkMage::CheckAnimationEvents()
{
	CBaseAnimated::CheckAnimationEvents();

	if (m_Velocity.IsNull())
	{
		ResetAnimation();
		PauseAnimation(true);
	}
	else
	{
		PauseAnimation(false);

		switch (m_ViewDirection)
		{
		case ViewDirection_t::Up:
			SetCurrentAnimation("run_up");
			break;
		case ViewDirection_t::Down:
			SetCurrentAnimation("run_down");
			break;
		case ViewDirection_t::Left:
			SetCurrentAnimation("run_left");
			break;
		case ViewDirection_t::Right:
			SetCurrentAnimation("run_right");
			break;
		}
	}
}
