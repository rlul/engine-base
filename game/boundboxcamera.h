#pragma once
#include "staticcamera.h"

class CBoundBoxCamera : public CStaticCamera
{
public:
	CBoundBoxCamera();
	virtual ~CBoundBoxCamera() override;

	virtual void Update(float dt) override;
	virtual void Render() const override;

	virtual void SetBoundBox(const Vector2D_t& mins, const Vector2D_t& maxs);
	virtual void SetBoundBoxSize(const Vector2D_t& size);

private:
	Vector2D_t m_BoundBoxMins, m_BoundBoxMaxs;
};


