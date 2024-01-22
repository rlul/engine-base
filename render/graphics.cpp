#include <cstdio>
#include "render/igraphics.h"
#include "graphicsapi.h"
#include "engine/iscenesystem.h"

class CGraphics : public IGraphics
{
public:
	CGraphics();
	~CGraphics();

	bool Setup() override;
	void Shutdown() override;

	bool Frame() override;

private:
	CGraphicsAPI* m_pAPI;
};

CGraphics g_Graphics;
IGraphics* Graphics()
{
	return &g_Graphics;
}

CGraphics::CGraphics()
	: m_pAPI(new CGraphicsAPI)
{
	
}

CGraphics::~CGraphics()
{
	delete m_pAPI;
}

bool CGraphics::Setup()
{
	if (m_pAPI == nullptr)
	{
		printf("CGraphics uninitialized!\n");
		return false;
	}
	if (!m_pAPI->Setup())
	{
		printf("Failed to setup graphics API!\n");
		return false;
	}

	return true;
}

void CGraphics::Shutdown()
{
	
}

bool CGraphics::Frame()
{
	m_pAPI->BeginScene();

	m_pAPI->EndScene();

	return true;
}
