#include "SceneManager.h"

SceneManager::SceneManager(Scene* begin)
{
	this->nowScene = begin;
	this->nextScene = nullptr;
}
SceneManager::~SceneManager()
{
	if (this->nowScene)
	{
		delete nowScene;
		nowScene = nullptr;
	}
	if (this->nextScene)
	{
		delete nextScene;
		nextScene = nullptr;
	}
}
void SceneManager::ChangeScene(Scene* next)
{
	this->nextScene = next;
}
void SceneManager::SceneUpdate()
{
	Scene::EntityUpdate(nowScene);
	ChangeAdaptation();
}
void SceneManager::ChangeAdaptation()
{
	if (nextScene != nullptr)
	{
		delete nowScene;
		nowScene = nextScene;
		nowScene->Enter();
		nextScene = nullptr;
	}
}
Scene* SceneManager::Get()
{
	return this->nowScene;
}