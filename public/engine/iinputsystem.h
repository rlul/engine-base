#pragma once
#include "subsystems.h"

#define INPUT_SYSTEM_VERSION "InputSystem001"

#define KEY_UP			0
#define KEY_DOWN		(1 << 0)
#define KEY_PRESSED		(1 << 1)
#define KEY_RELEASED	(1 << 2)
#define KEY_INVALID		(1 << 31)

typedef int KeyCode_t;

abstract_class IInputSystem : public IAppSystem
{
public:
	virtual ~IInputSystem() = default;

	virtual bool Setup() = 0;

	virtual void Update() = 0;

	virtual void SetMousePosition(int x, int y) = 0;
	virtual void GetMousePosition(int& x, int& y) = 0;

	virtual void SetMouseDelta(int dx, int dy) = 0;
	virtual void GetMouseDelta(int& dx, int& dy) = 0;

	virtual void SetKeyState(KeyCode_t key, bool down) = 0;
	virtual void SetKeyForBind(const char* name, KeyCode_t key) = 0;
	virtual KeyCode_t GetKeyForBind(const char* name) = 0;

	virtual bool IsKeyPressed(KeyCode_t key) = 0;
	virtual bool IsKeyDown(KeyCode_t key) = 0;
	virtual bool IsKeyReleased(KeyCode_t key) = 0;
	virtual bool IsKeyUp(KeyCode_t key) = 0;
};
