#include "subsystem.h"
#include "engine/iinputsystem.h"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

#include "game/ibaseentity.h"
#include "game/igameclient.h"

class CInputSystem : public IInputSystem
{
public:
	CInputSystem() = default;
	~CInputSystem() override = default;

	bool Setup() override;
	void Shutdown() override;
	const char* GetSystemName() const override { return INPUT_SYSTEM_VERSION; }

    void Update() override;
	void SetMousePosition(int x, int y) override;
	void GetMousePosition(int& x, int& y) override;
	void SetMouseDelta(int dx, int dy) override;
	void GetMouseDelta(int& dx, int& dy) override;
	void SetKeyState(KeyCode_t key, bool down) override;
	KeyState_t GetKeyState(KeyCode_t key) override;
	bool IsKeyDown(KeyCode_t key) override;
	bool IsKeyPressed(KeyCode_t key) override;
	bool IsKeyUp(KeyCode_t key) override;
	void SetKeyForBind(const char* name, KeyCode_t key) override;
	KeyCode_t GetKeyForBind(const char* name) override;

private:
	virtual bool MakeMove();
	virtual void KeyDown(KeyState_t& key_state);
	virtual void KeyUp(KeyState_t& key_state);

private:
	int m_iMouseX = 0;
	int m_iMouseY = 0;
	int m_iMouseDX = 0;
	int m_iMouseDY = 0;
	std::unordered_map<KeyCode_t, KeyState_t> m_iKeyStates;
	std::unordered_map<std::string, KeyCode_t> m_iKeyBinds;
	
};

CInputSystem g_InputSystem;
CREATE_SINGLE_SYSTEM( CInputSystem, IInputSystem, INPUT_SYSTEM_VERSION, g_InputSystem );

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

KeyState_t CInputSystem::GetKeyState(KeyCode_t key)
{
	return m_iKeyStates[key];
}

bool CInputSystem::IsKeyDown(KeyCode_t key)
{
	return m_iKeyStates[key] & KEY_DOWN;
}

bool CInputSystem::IsKeyUp(KeyCode_t key)
{
	return m_iKeyStates[key] & KEY_UP;
}

bool CInputSystem::IsKeyPressed(KeyCode_t key)
{
	return m_iKeyStates[key] & KEY_PRESSED;
}

void CInputSystem::SetKeyForBind(const char* name, KeyCode_t key)
{
	m_iKeyBinds[name] = key;
}

KeyCode_t CInputSystem::GetKeyForBind(const char* name)
{
	return m_iKeyBinds[name];
}

bool CInputSystem::MakeMove()
{
	IBaseEntity* player = g_pGameClient->GetLocalPlayer();

	if (!player)
		return false;

	bool move_up = IsKeyPressed(GetKeyForBind("up"));
	bool move_down = IsKeyPressed(GetKeyForBind("down"));
	bool move_left = IsKeyPressed(GetKeyForBind("left"));
	bool move_right = IsKeyPressed(GetKeyForBind("right"));
	MoveInfo_t move_info{};

	if (move_up && !move_down)
	{
		move_info.forwardmove = -1;
	}

	if (!move_up && move_down)
	{
		move_info.forwardmove = 1;
	}

	if (move_left && !move_right)
	{
		move_info.sidemove = -1;
	}

	if (!move_left && move_right)
	{
		move_info.sidemove = 1;
	}

	player->MakeMove(move_info);

	return false;
}

void CInputSystem::KeyDown(KeyState_t& key_state)
{
	if ((key_state & KEY_DOWN) && (key_state & KEY_PRESSED))
		return;

	if (!(key_state & KEY_PRESSED)) 
	{
		key_state |= KEY_PRESSED;
		return;
	}

	if (!(key_state & KEY_DOWN)) 
	{
		key_state |= KEY_DOWN;
		return;
	}
}

void CInputSystem::KeyUp(KeyState_t& key_state)
{
	if (key_state & KEY_UP)
		return;

	key_state = KEY_UP;
}
