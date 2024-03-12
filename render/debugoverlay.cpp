#include "debugoverlay.h"
#include <SDL3/SDL.h>
#include <imgui.h>

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl3.h"

bool CDebugOverlay::Setup(SDL_Window* window, SDL_GLContext gl_context)
{
	m_pWindow = window;
	m_OpenGLContext = gl_context;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL3_InitForOpenGL(m_pWindow, m_OpenGLContext);
	ImGui_ImplOpenGL3_Init("#version 130");

	return true;
}

bool CDebugOverlay::Frame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Text("123");

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return true;
}

void CDebugOverlay::ProcessEvent(void* sdl_event)
{
	ImGui_ImplSDL3_ProcessEvent((SDL_Event*)sdl_event);
}

CDebugOverlay g_DebugOverlay;
CDebugOverlay* g_pDebugOverlay = &g_DebugOverlay;
