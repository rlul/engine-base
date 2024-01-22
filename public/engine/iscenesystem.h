#pragma once
#include "engine.h"
#include "scene2d.h"

abstract_class ISceneSystem
{
public:
	virtual bool LoadScene(CScene2D* scene) = 0;
	virtual bool LoadScene(const char* path) = 0;
	virtual CScene2D* GetCurrentScene() const = 0;

	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};

ENGINE_API ISceneSystem* SceneSystem();
