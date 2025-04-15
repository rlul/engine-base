#pragma once
#include "gamemath.h"

class CRenderView 
{
public:
	CRenderView()
		: m_Pos(), m_flScale(1.0f), m_ViewMatrix()
	{
	}

	void UpdateViewMatrix()
	{
		m_ViewMatrix = 
			Matrix3x3_t::Translate({ m_Size.x * 0.5f, m_Size.y * 0.5f }) *
			Matrix3x3_t::Scale({ m_flScale, m_flScale }) *
			Matrix3x3_t::Translate({ -m_Pos.x, -m_Pos.y });
	}

	Vector2D_t m_Pos, m_Size;
	float m_flScale;
	Matrix3x3_t m_ViewMatrix;
};
