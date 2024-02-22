#pragma once
#include "engine/module.h"
#include "subsystem/iappsystem.h"
#include "scene2d.h"

#define SCENE_SYSTEM_VERSION "SceneSystem001"

abstract_class ISceneSystem : public IAppSystem
{
public:
	virtual bool LoadScene(CScene2D* scene) = 0;
	virtual bool LoadScene(const char* path) = 0;
	virtual CScene2D* GetCurrentScene() const = 0;

	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};

ENGINE_API ISceneSystem* SceneSystem();
