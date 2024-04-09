#pragma once
#include "staticcamera.h"

class CFollowCamera : public CStaticCamera
{
public:
	CFollowCamera();
	virtual ~CFollowCamera() override;

	virtual void Update(float dt) override;
};
