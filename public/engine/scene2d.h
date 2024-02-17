#pragma once

class CScene2D
{
public:
	CScene2D();
	virtual ~CScene2D();

	virtual void Initialize();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render();

	// temp
private:
	int m_uColor;
};