#include "boundboxcamera.h"
#include "subsystems.h"
#include "game/igameclient.h"
#include "game/ibaseentity.h"

CBoundBoxCamera::CBoundBoxCamera()
	: CStaticCamera()
{
}

CBoundBoxCamera::~CBoundBoxCamera()
{
	delete m_pRenderView;
}

void CBoundBoxCamera::Update(float dt)
{
	CStaticCamera::Update(dt);

}

void CBoundBoxCamera::Render() const
{
	CStaticCamera::Render();


	//SDL_RenderDrawRectF()
	
}

void CBoundBoxCamera::SetBoundBox(const Vector2D_t& mins, const Vector2D_t& maxs)
{
	m_BoundBoxMins = mins; m_BoundBoxMaxs = maxs;
}

void CBoundBoxCamera::SetBoundBoxSize(const Vector2D_t& size)
{
	m_BoundBoxMins =  -size / 2;
	m_BoundBoxMaxs = size / 2;
}
