#include "scene2d.h"
#include <algorithm>

CScene2D::CScene2D()
	: m_uColor(0)
{
}

CScene2D::~CScene2D()
{
	
}

void CScene2D::Initialize()
{

}

void CScene2D::Destroy()
{
	
}

void CScene2D::Update(float deltatime)
{
	m_uColor += 10 * deltatime;
	m_uColor = std::clamp(m_uColor, 0, 255);
}

void CScene2D::Render()
{
	
}
