#include "engine/iscenesystem.h"

class CSceneSystem : public ISceneSystem
{
	APPSYSTEM_OBJECT(SCENE_SYSTEM_VERSION)

public:
	CSceneSystem();
	~CSceneSystem() override;

	bool LoadScene(CScene2D* scene) override;
	bool LoadScene(const char* index) override;
	CScene2D* GetCurrentScene() const override;

	void Update(float deltatime) override;
	void Render() override;

private:
	CScene2D* m_pCurrentScene;
};

CSceneSystem g_SceneSystem;
ISceneSystem* SceneSystem()
{
	return &g_SceneSystem;
}

bool CSceneSystem::Setup()
{
	m_bIsSetup = true;
	return true;
}

void CSceneSystem::Shutdown()
{
	m_bIsSetup = false;
}

CSceneSystem::CSceneSystem()
	: m_bIsSetup(false), m_pCurrentScene(nullptr)
{
}

CSceneSystem::~CSceneSystem()
{
	delete m_pCurrentScene;
}

bool CSceneSystem::LoadScene(CScene2D* scene)
{
	m_pCurrentScene = scene;
	return true;
}

bool CSceneSystem::LoadScene(const char* index)
{
	return false;
}

CScene2D* CSceneSystem::GetCurrentScene() const
{
	return m_pCurrentScene;
}

void CSceneSystem::Update(float deltatime)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update(deltatime);
}

void CSceneSystem::Render()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}
