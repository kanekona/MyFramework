#include "Entity.h"

Entity::Entity()
{
	active = true;
	stateCount = KL_ENTITY_NORMAL;
	layer = Layer::Default;
	tag = typeid(*this).name();
}
Entity::~Entity()
{
	//q‚Ì‰ğ•ú
	for (auto& it : childs)
	{
		delete it;
	}
	childs.clear();
	for (auto& it : plansChilds)
	{
		delete it;
	}
	plansChilds.clear();
}
void Entity::Update()
{

}
void Entity::Enter()
{

}
void Entity::Destroy()
{
	stateCount = KL_ENTITY_KILL;
}
void Entity::SetActive(const bool isActive)
{
	active = isActive;
}
bool Entity::GetActive() const
{
	return active;
}
void Entity::RegisterChildren()
{
	/*for (auto id : plansChilds)
	{
		childs.emplace_back(id);
		id->Enter();

		id->RegisterChildren();
	}
	plansChilds.clear();*/
	for (auto it = plansChilds.begin(); it != plansChilds.end();)
	{
		childs.emplace_back(*it);
		(*it)->Enter();
		(*it)->RegisterChildren();
		it = plansChilds.erase(it);
	}
}
void Entity::KillChildren()
{
	for (auto id = childs.begin(); id != childs.end();)
	{
		if (Entity::GetStateCount(*id) == KL_ENTITY_KILL)
		{
			delete *id;
			id = childs.erase(id);
		}
		else
		{
			//Ä‹N‚Åq‚Ìq‚ğíœ‚·‚é
			(*id)->KillChildren();
			++id;
		}
	}
}
void Entity::SetChildren(Entity* child)
{
	plansChilds.emplace_back(child);
}
int Entity::GetStateCount(Entity* entity)
{
	return entity->stateCount;
}
void Entity::Destroy(Entity* entity)
{
	entity->Destroy();
}
void Entity::Update(Entity* entity)
{
	if (entity->active)
	{
		entity->Update();
	}
}
void Entity::Enter(Entity* entity)
{
	entity->Enter();
}
void Entity::ChildrenUpdate(Entity* entity)
{
	for (auto id : entity->childs)
	{
		if (id->active)
		{
			Entity::Update(id);
			Entity::ChildrenUpdate(id);
		}
	}
}
void Entity::ChildrenStateAdaptation(Entity* entity)
{
	//íœ—\’è‚ğíœ
	entity->KillChildren();
	//“o˜^—\’è‚ğ“o˜^
	entity->RegisterChildren();
}
size_t Entity::ChildCount() const
{
	return childs.size();
}
Entity* Entity::GetChild(const size_t index)
{
	return childs[index];
}
Entity* Entity::GetChild(const Layer key)
{
	for (auto& it : childs)
	{
		if (it->layer == key)
		{
			return it;
		}
	}
	for (auto& it : plansChilds)
	{
		if (it->layer == key)
		{
			return it;
		}
	}
	return nullptr;
}
std::vector<Entity*>* Entity::GetChilds()
{
	return &childs;
}