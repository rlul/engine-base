#include "graphicsapi.h"
#include "base/icommandline.h"
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
		window_width = CommandLine()->GetParam<int>("width");
	if (CommandLine()->HasParam("height"))
		window_height = CommandLine()->GetParam<int>("height");

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

	return true;
}

void CGraphicsAPI::Shutdown()
{
	SDL_GL_DeleteContext(m_pOpenGLContext);
	SDL_DestroyWindow(m_pWindow);
}

void CGraphicsAPI::BeginScene()
{
}

void CGraphicsAPI::EndScene()
{
	SDL_GL_SwapWindow(m_pWindow);
}

