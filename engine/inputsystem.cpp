#include "inputsystem.h"
#include "subsystem.h"
#include "game/ibaseentity.h"
#include "game/igameclient.h"

CInputSystem g_InputSystem;
CREATE_SINGLE_SYSTEM(CInputSystem, IInputSystem, INPUT_SYSTEM_VERSION, g_InputSystem);

bool CInputSystem::Setup()
{
	SetKeyForBind("up", 'w');
	SetKeyForBind("down", 's');
	SetKeyForBind("left", 'a');
	SetKeyForBind("right", 'd');

	return true;
}

void CInputSystem::Shutdown()
{

}

void CInputSystem::Update()
{
	MakeMove();
}

void CInputSystem::SetMousePosition(int x, int y)
{
	m_iMouseX = x;
	m_iMouseY = y;
}

void CInputSystem::GetMousePosition(int& x, int& y)
{
	x = m_iMouseX;
	y = m_iMouseY;
}

void CInputSystem::SetMouseDelta(int dx, int dy)
{
	m_iMouseDX = dx;
	m_iMouseDY = dy;
}

void CInputSystem::GetMouseDelta(int& dx, int& dy)
{
	dx = m_iMouseDX;
	dy = m_iMouseDY;
}

void CInputSystem::SetKeyState(KeyCode_t key, bool down)
{
	if (down)
	{
		KeyDown(m_iKeyStates[key]);
	}
	else
	{
		KeyUp(m_iKeyStates[key]);
	}
}

void CInputSystem::SetKeyForBind(const char* name, KeyCode_t key)
{
	m_iKeyBinds[name] = key;
}

KeyCode_t CInputSystem::GetKeyForBind(const char* name)
{
	return m_iKeyBinds[name];
}


bool CInputSystem::IsKeyPressed(KeyCode_t key)
{
	return GetKeyState(key) & KEY_PRESSED;
}
bool CInputSystem::IsKeyDown(KeyCode_t key)
{
	return GetKeyState(key) & KEY_DOWN;
}
bool CInputSystem::IsKeyReleased(KeyCode_t key)
{
	return GetKeyState(key) & KEY_RELEASED;
}
bool CInputSystem::IsKeyUp(KeyCode_t key)
{
	return GetKeyState(key) & KEY_UP;
}

int CInputSystem::GetKeyState(KeyCode_t key)
{
	auto& key_state = m_iKeyStates[key];

	int result = 0;
	int impulsedown, impulseup, down;

	impulsedown = key_state.state & 2;
	impulseup = key_state.state & 4;
	down = key_state.state & 1;

	if (impulsedown)
	{
		result |= KEY_PRESSED;
	}

	if (impulseup)
	{
		result |= KEY_RELEASED;
	}

	if (down)
	{
		result |= KEY_DOWN;
	}
	else
	{
		result |= KEY_UP;
	}

	key_state.state &= 1;	// clear impulse
	return result;
}

void CInputSystem::KeyDown(KeyState_t& key_state)
{
	if (key_state.down)
		return;

	if (!key_state.down)
		key_state.down = true;

	if (key_state.state & 1)
		return;		// still down
	key_state.state |= 1 + 2;	// down + impulse down
}

void CInputSystem::KeyUp(KeyState_t& key_state)
{
	key_state.down = false;
	key_state.state = 4;	// impulse up
}

bool CInputSystem::MakeMove()
{
	IBaseEntity* player = g_pGameClient->GetLocalPlayer();

	if (!player)
		return false;

	bool move_up = IsKeyDown(GetKeyForBind("up"));
	bool move_down = IsKeyDown(GetKeyForBind("down"));
	bool move_left = IsKeyDown(GetKeyForBind("left"));
	bool move_right = IsKeyDown(GetKeyForBind("right"));
	MoveInfo_t move_info{};

	if (move_up && !move_down)
	{
		move_info.forwardmove = 1;
		move_info.viewdirection = ViewDirection_t::Up;
	}

	if (!move_up && move_down)
	{
		move_info.forwardmove = -1;
		move_info.viewdirection = ViewDirection_t::Down;
	}

	if (move_left && !move_right)
	{
		move_info.sidemove = -1;
		move_info.viewdirection = ViewDirection_t::Left;
	}

	if (!move_left && move_right)
	{
		move_info.sidemove = 1;
		move_info.viewdirection = ViewDirection_t::Right;
	}

	player->MakeMove(move_info);

	return false;
}
