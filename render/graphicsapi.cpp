#include "graphicsapi.h"
#include "core/icommandline.h"
#include <glad/glad.h>
#include <cstdio>

CGraphicsAPI::CGraphicsAPI()
	: m_pWindow(), m_pOpenGLContext()
{
	
}

CGraphicsAPI::~CGraphicsAPI()
{
	
}

bool CGraphicsAPI::Setup()
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

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_pWindow = SDL_CreateWindow("engine-demo", window_width, window_height, SDL_WINDOW_OPENGL);
	if (m_pWindow == NULL)
	{
		printf("SDL_CreateWindow failed! (%s)\n", SDL_GetError());
		return false;
	}

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
	return true;
}

void CGraphicsAPI::Shutdown()
{
	SDL_GL_DeleteContext(m_pOpenGLContext);
	SDL_DestroyWindow(m_pWindow);
}

void CGraphicsAPI::BeginScene()
{
	glClearColor(.1f, .1f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CGraphicsAPI::EndScene()
{
	SDL_GL_SwapWindow(m_pWindow);
}
