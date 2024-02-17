#include "render/igraphics.h"
#include "engine/iscenesystem.h"
#include "core/icommandline.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <cstdio>

class CGraphics : public IGraphics
{
	APPSYSTEM_OBJECT(GRAPHICS_VERSION)

public:
	CGraphics();
	~CGraphics();

	bool Frame() override;

private:
	void BeginScene();
	void EndScene();

private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_pOpenGLContext;
};

CGraphics g_Graphics;
IGraphics* Graphics()
{
	return &g_Graphics;
}

bool CGraphics::Setup()
{
	int window_width = 1280, window_height = 720;

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL_Init failed! (%s)\n", SDL_GetError());
		return false;
	}


	if (CommandLine()->HasParam("width"))
		window_width = CommandLine()->GetParamInt("width");
	if (CommandLine()->HasParam("height"))
		window_height = CommandLine()->GetParamInt("height");



	m_pWindow = SDL_CreateWindow("engine-demo", window_width, window_height, SDL_WINDOW_OPENGL);
	if (m_pWindow == NULL)
	{
		printf("SDL_CreateWindow failed! (%s)\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_pOpenGLContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pOpenGLContext == NULL)
	{
		printf("SDL_GL_CreateContext failed! (%s)\n", SDL_GetError());
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("Failed while trying to load OpenGL context!\n");
		return false;
	}

	printf("Initialized OpenGL %s\n", glGetString(GL_VERSION));
	printf("Video Adapter: %s\n", glGetString(GL_RENDERER));

	m_bIsSetup = true;
	return true;
}

void CGraphics::Shutdown()
{
	SDL_GL_DeleteContext(m_pOpenGLContext);
	SDL_DestroyWindow(m_pWindow);

	m_bIsSetup = false;
}

CGraphics::CGraphics()
	: m_bIsSetup(false), m_pWindow(nullptr), m_pOpenGLContext(nullptr)
{
}

CGraphics::~CGraphics()
{
	
}

bool CGraphics::Frame()
{
	BeginScene();

	EndScene();

	return true;
}

void CGraphics::BeginScene()
{
	glClearColor(.1f, .1f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CGraphics::EndScene()
{
	SDL_GL_SwapWindow(m_pWindow);
}