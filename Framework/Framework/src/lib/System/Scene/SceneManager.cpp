#include "SceneManager.h"
#include "Scene.h"

CSceneManager::CSceneManager(CScene* begin)
{
	nowScene = begin;
	nextScene = nullptr;
}
CSceneManager::~CSceneManager()
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
void CSceneManager::ChangeScene(CScene* next)
{
	nextScene = next;
}
void CSceneManager::SceneUpdate()
{
	CScene::EntityUpdate(nowScene);
	ChangeAdaptation();
}
void CSceneManager::ChangeAdaptation()
{
	if (nextScene != nullptr)
	{
		delete nowScene;
		nowScene = nextScene;
		nowScene->Entry();
		nextScene = nullptr;
	}
}
CScene* CSceneManager::Get()
{
	return nowScene;
}