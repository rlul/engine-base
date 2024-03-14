#include "debugoverlay.h"
#include "core/ifilesystem.h"
#include "subsystems.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <imgui.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <backends/imgui_impl_sdl2.h>
#include <cstdio>

#include "engine/iengine.h"

SDL_Texture* texture = nullptr;

bool CDebugOverlay::Setup(SDL_Window* window, SDL_Renderer* renderer)
{
	m_pWindow = window;
	m_pRenderer = renderer;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL2_InitForSDLRenderer(m_pWindow, m_pRenderer);
	ImGui_ImplSDLRenderer2_Init(m_pRenderer);

	auto file = g_pFileSystem->Open("textures/monke.png", "core", IFileSystem::OPEN_READ_WRITE);
	auto size = g_pFileSystem->Size(file);
	char* buf = new char[size] {0, };
	g_pFileSystem->Read(file, buf, size);
	auto rw = SDL_RWFromMem(buf, size);
	auto surface = IMG_Load_RW(rw, 1);
	texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	delete[] buf;
	g_pFileSystem->Close(file);

	return true;
}

void CDebugOverlay::Shutdown()
{
	SDL_DestroyTexture(texture);
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

bool CDebugOverlay::Frame()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ShowFPS();
	ImGui::Image(texture, ImVec2(372, 404));
	if (ImGui::Button("monke"))
	{
		printf("bob\n");
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	return true;
}

void CDebugOverlay::ProcessEvent(void* sdl_event)
{
	ImGui_ImplSDL2_ProcessEvent((SDL_Event*)sdl_event);
}

void CDebugOverlay::ShowFPS() const
{
	char buf[32];
	static float frames_per_second = 0.f, total_time = 0.f;

	++frames_per_second;
	total_time += g_pEngine->GetFrameTime();

	sprintf(buf, "FPS: %f", frames_per_second / total_time);
	ImGui::Text(buf);

	if (total_time > 1.f)
		frames_per_second = total_time = 0.f;
}

CDebugOverlay g_DebugOverlay;
CDebugOverlay* g_pDebugOverlay = &g_DebugOverlay;
