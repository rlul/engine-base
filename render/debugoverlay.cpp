#include "debugoverlay.h"
#include "render/igraphics.h"
#include "engine/iengine.h"
#include "engine/iinputsystem.h"
#include "engine/itilemap.h"
#include "core/ifilesystem.h"
#include "game/igameclient.h"
#include "game/ientitylist.h"
#include "game/ibaseentity.h"
#include "game/icamera.h"
#include "subsystems.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <imgui.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <backends/imgui_impl_sdl2.h>
#include <cstdio>

SDL_Texture* texture = nullptr;

CDebugOverlay::CDebugOverlay()
	: m_bShouldDraw(true), m_pWindow(nullptr), m_pRenderer(nullptr)
{
}

CDebugOverlay::~CDebugOverlay()
{
}

bool CDebugOverlay::Setup(SDL_Window* window, SDL_Renderer* renderer)
{
	m_pWindow = window;
	m_pRenderer = renderer;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplSDL2_InitForSDLRenderer(m_pWindow, m_pRenderer);
	ImGui_ImplSDLRenderer2_Init(m_pRenderer);

	auto file = g_pFileSystem->Open("textures/coconut.png", "core", IFileSystem::OPEN_READ_WRITE);
	auto size = g_pFileSystem->Size(file);
	char* buf = new char[size] { 0, };
	g_pFileSystem->Read(file, buf, size);

	auto rw = SDL_RWFromMem(buf, size);
	auto surface = IMG_Load_RW(rw, 1);

	delete[] buf;
	g_pFileSystem->Close(file);

	if (!surface)
	{
		printf("Failed to load surface!\n");
		return false;
	}

	texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	if (!texture)
	{
		printf("Failed to create texture from surface!\n");
		return false;
	}

	SDL_FreeSurface(surface);

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
	if (g_pInputSystem->IsKeyPressed(SDLK_INSERT))
		m_bShouldDraw = !m_bShouldDraw;

	if (!m_bShouldDraw)
		return false;

	if (g_pEngine->IsInGame())
	{
		DrawWorldOrigin();
		DrawCameraPos();
		DrawEntityPos();
		DrawEntityBounds();
	}

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	char text_buffer[256];

	sprintf(text_buffer, "FPS: %f\n", CalculateFPS());
	ImGui::Text(text_buffer);

	auto current_scene = g_pEngine->GetCurrentScene();
	sprintf(text_buffer, "Current scene: %s", current_scene ? current_scene->GetName().c_str() : "<NONE>");
	ImGui::Text(text_buffer);

	if (ImGui::Button("Load Level"))
		g_pGameClient->LoadLevel("testmap");
	
	if (ImGui::Button("Unload Level"))
		g_pGameClient->UnloadLevel();

	ImGui::Image(texture, ImVec2(256, 256));

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

	return true;
}

void CDebugOverlay::ProcessEvent(void* sdl_event)
{
	ImGui_ImplSDL2_ProcessEvent((SDL_Event*)sdl_event);
}

bool CDebugOverlay::ShouldDraw()
{
	return m_pRenderer;
}

float CDebugOverlay::CalculateFPS()
{
	float result;
	static float frames_per_second = 0.f, total_time = 0.f;

	++frames_per_second;
	total_time += g_pEngine->GetFrameTime();
	result = frames_per_second / total_time;

	if (total_time > 1.f)
		frames_per_second = total_time = 0.f;

	return result;
}

void CDebugOverlay::DrawEntityPos()
{
	Uint8 old_r, old_g, old_b, old_a;
	SDL_GetRenderDrawColor(m_pRenderer, &old_r, &old_g, &old_b, &old_a);
	SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		float world_x, world_y;
		float screen_x, screen_y;

		auto entity = g_pEntityList->GetEntity(i);
		entity->GetPos(world_x, world_y);
		g_pGraphics->WorldToScreen(world_x, world_y, screen_x, screen_y);

		SDL_RenderDrawLineF(m_pRenderer, screen_x - 5, screen_y, screen_x + 5, screen_y);
		SDL_RenderDrawLineF(m_pRenderer, screen_x, screen_y - 5, screen_x, screen_y + 5);
	}

	SDL_SetRenderDrawColor(m_pRenderer, old_r, old_g, old_b, old_a);
}

void CDebugOverlay::DrawEntityBounds()
{
	Uint8 old_r, old_g, old_b, old_a;
	SDL_GetRenderDrawColor(m_pRenderer, &old_r, &old_g, &old_b, &old_a);
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

	for (int i = 0; i < g_pEntityList->GetEntityCount(); i++)
	{
		Vector2D_t world_mins, world_maxs;
		Vector2D_t screen_bl, screen_tl, screen_br, screen_tr;

		auto entity = g_pEntityList->GetEntity(i);
		entity->GetWorldBounds(world_mins, world_maxs);
		g_pGraphics->WorldToScreen(world_mins, screen_bl);
		g_pGraphics->WorldToScreen(world_mins.x, world_maxs.y, screen_tl.x, screen_tl.y);
		g_pGraphics->WorldToScreen(world_maxs, screen_tr);
		g_pGraphics->WorldToScreen(world_maxs.x, world_mins.y, screen_br.x, screen_br.y);

		SDL_RenderDrawLineF(m_pRenderer, screen_bl.x, screen_bl.y, screen_tl.x, screen_tl.y);
		SDL_RenderDrawLineF(m_pRenderer, screen_tl.x, screen_tl.y, screen_tr.x, screen_tr.y);
		SDL_RenderDrawLineF(m_pRenderer, screen_tr.x, screen_tr.y, screen_br.x, screen_br.y);
		SDL_RenderDrawLineF(m_pRenderer, screen_br.x, screen_br.y, screen_bl.x, screen_bl.y);
	}

	SDL_SetRenderDrawColor(m_pRenderer, old_r, old_g, old_b, old_a);
}

void CDebugOverlay::DrawCameraPos()
{
	Uint8 old_r, old_g, old_b, old_a;
	SDL_GetRenderDrawColor(m_pRenderer, &old_r, &old_g, &old_b, &old_a);
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 255, 255);

	Vector2D_t world_pos, screen_pos;
	world_pos = g_pGameClient->GetActiveCamera()->GetPos();
	g_pGraphics->WorldToScreen(world_pos, screen_pos);

	SDL_RenderDrawLineF(m_pRenderer, screen_pos.x - 15, screen_pos.y, screen_pos.x + 15, screen_pos.y);
	SDL_RenderDrawLineF(m_pRenderer, screen_pos.x, screen_pos.y - 15, screen_pos.x, screen_pos.y + 15);

	SDL_SetRenderDrawColor(m_pRenderer, old_r, old_g, old_b, old_a);
}

void CDebugOverlay::DrawWorldOrigin()
{
	Uint8 old_r, old_g, old_b, old_a;
	SDL_GetRenderDrawColor(m_pRenderer, &old_r, &old_g, &old_b, &old_a);
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

	float screen_x, screen_y;
	g_pGraphics->WorldToScreen(0, 0, screen_x, screen_y);

	SDL_RenderDrawLineF(m_pRenderer, screen_x - 15, screen_y, screen_x + 15, screen_y);
	SDL_RenderDrawLineF(m_pRenderer, screen_x, screen_y - 15, screen_x, screen_y + 15);

	SDL_SetRenderDrawColor(m_pRenderer, old_r, old_g, old_b, old_a);
}

CDebugOverlay g_DebugOverlay;
CDebugOverlay* g_pDebugOverlay = &g_DebugOverlay;
