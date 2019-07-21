#include "SceneManager.h"

SceneManager::SceneManager(Scene* begin)
{
	nowScene = begin;
	nextScene = nullptr;
}
SceneManager::~SceneManager()
{
	if (nowScene)
	{
		delete nowScene;
		nowScene = nullptr;
	}
	if (nextScene)
	{
		delete nextScene;
		nextScene = nullptr;
	}
}
void SceneManager::ChangeScene(Scene* next)
{
	nextScene = next;
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
	return nowScene;
}