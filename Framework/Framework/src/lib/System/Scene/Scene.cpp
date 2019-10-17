#include "Scene.h"
#include "Engine\Framework.h"
#include "Window\Window.h"
CScene::CScene()
{
	camera = new CCamera2D(CBox2D(CVec2(), CFramework::Get()->GetWindow()->GetSize()));
}
CScene::~CScene()
{
	for (auto id : entitys)
	{
		delete id;
	}
	entitys.clear();
	for (auto id : plansEntity)
	{
		delete id;
	}
	plansEntity.clear();
	delete camera;
}
void CScene::Entry()
{

}
void CScene::SetEntity(CEntity* entity)
{
	plansEntity.emplace_back(entity);
}
void CScene::RegisterEntity()
{
	/*for (auto it = plansEntity.begin(); it != plansEntity.end();)
	{
		entitys.emplace_back(*it);
		Entity::Entry(*it);
		it = plansEntity.erase(it);
	}*/
	for (auto it : plansEntity)
	{
		entitys.emplace_back(it);
		CEntity::Entry(it);
	}
	plansEntity.clear();
}
void CScene::KillEntity()
{
	ENSUREMSG(true, "‚±‚Ìˆ—‚ÍŽg—p•s‰Â‚Å‚·");
	/*for (auto id = entitys.begin(); id != entitys.end();)
	{
		if (CEntity::GetStateCount(*id) == KL_ENTITY_KILL)
		{
			delete *id;
			*id = nullptr;
			id = entitys.erase(id);
		}
		else
		{
			++id;
		}
	}*/
}
CRenderingManager* CScene::GetRenderingManager()
{
	return &renderingManager;
}
CCamera2D* CScene::GetCamera()
{
	return camera;
}
void CScene::EntityStateAdaptation(CScene* scene)
{
	//íœ—\’è‚ðíœ
	scene->KillEntity();
	//“o˜^—\’è‚ð“o˜^
	scene->RegisterEntity();
}
void CScene::EntityUpdate(CScene* scene)
{
	//Entity Update
	for (auto id : scene->entitys)
	{
		CEntity::Update(id);
		CEntity::ChildrenUpdate(id);
	}
	//Camera Update
	scene->camera->Update();
	//Rendering
	CRenderingManager::Render(&scene->renderingManager);
	//Entity State Check
	CScene::EntityStateAdaptation(scene);
	for (auto it : scene->entitys)
	{
		CEntity::ChildrenStateAdaptation(it);
	}
	//Rendering State Check
	CRenderingManager::AllSpriteAdaptation(&scene->renderingManager);
}
size_t CScene::EntityCount() const
{
	return entitys.size();
}
CEntity* CScene::GetEntity(const size_t num)
{
	return entitys[num];
}
std::vector<CEntity*>* CScene::GetEntitys()
{
	return &entitys;
}
#ifdef KL_DEBUG
void Scene::Debug()
{
	std::cout << "SceneTag : " << tag << "\n";
	for (auto it : entitys)
	{
		std::cout << "Entitys : " << it->tag << "\n";
	}
}
#endif