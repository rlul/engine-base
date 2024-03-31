#pragma once
#include "engine/iinputsystem.h"
#include <unordered_map>
#include <string>

struct KeyState_t
{
	bool down;
	int state;
};

class CInputSystem : public IInputSystem
{
public:
	CInputSystem() = default;
	virtual ~CInputSystem() override = default;

	virtual bool Setup() override;
	virtual void Shutdown() override;
	virtual const char* GetSystemName() const override { return INPUT_SYSTEM_VERSION; }

	virtual void Update() override;
	virtual void SetMousePosition(int x, int y) override;
	virtual void GetMousePosition(int& x, int& y) override;
	virtual void SetMouseDelta(int dx, int dy) override;
	virtual void GetMouseDelta(int& dx, int& dy) override;

	virtual void SetKeyState(KeyCode_t key, bool down) override;
	virtual void SetKeyForBind(const char* name, KeyCode_t key) override;
	virtual KeyCode_t GetKeyForBind(const char* name) override;

	virtual bool IsKeyPressed(KeyCode_t key) override;
	virtual bool IsKeyDown(KeyCode_t key) override;
	virtual bool IsKeyReleased(KeyCode_t key) override;
	virtual bool IsKeyUp(KeyCode_t key) override;

private:
	virtual int GetKeyState(KeyCode_t key);
	virtual void KeyDown(KeyState_t& key_state);
	virtual void KeyUp(KeyState_t& key_state);

	virtual bool MakeMove();

private:
	int m_iMouseX = 0;
	int m_iMouseY = 0;
	int m_iMouseDX = 0;
	int m_iMouseDY = 0;
	std::unordered_map<KeyCode_t, KeyState_t> m_iKeyStates;
	std::unordered_map<std::string, KeyCode_t> m_iKeyBinds;

};