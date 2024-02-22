#pragma once

class CScene2D
{
public:
	CScene2D();
	virtual ~CScene2D() = default;

	virtual void Initialize();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render();
};