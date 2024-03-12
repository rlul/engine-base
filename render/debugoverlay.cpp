#include "debugoverlay.h"
#include <SDL2/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <backends/imgui_impl_sdl2.h>

bool CDebugOverlay::Setup(SDL_Window* window, SDL_Renderer* renderer)
{
	m_pWindow = window;
	m_pRenderer = renderer;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL2_InitForSDLRenderer(m_pWindow, m_pRenderer);
	ImGui_ImplSDLRenderer2_Init(m_pRenderer);

	return true;
}

void CDebugOverlay::Shutdown()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

bool CDebugOverlay::Frame()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Text("123");

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	return true;
}

void CDebugOverlay::ProcessEvent(void* sdl_event)
{
	ImGui_ImplSDL2_ProcessEvent((SDL_Event*)sdl_event);
}

CDebugOverlay g_DebugOverlay;
CDebugOverlay* g_pDebugOverlay = &g_DebugOverlay;
