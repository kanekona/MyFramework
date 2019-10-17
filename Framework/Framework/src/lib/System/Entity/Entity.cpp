#include "Entity.h"
#include "System\System.h"
CEntity::CEntity()
	:tag(KL::ClassFromName<CEntity>())
	,active(true)
	,state(EState::NORMAL)
	,layer(ELayer::Default)
	,parent(nullptr)
{
}
CEntity::~CEntity()
{
	//Žq‚Ì‰ð•ú
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
void CEntity::Update()
{

}
void CEntity::Entry()
{

}
void CEntity::Destroy()
{
	state = EState::KILL;
}
void CEntity::SetActive(const bool isActive)
{
	active = isActive;
}
bool CEntity::GetActive() const
{
	return active;
}
void CEntity::RegisterChildren()
{
	/*for (auto id : plansChilds)
	{
		childs.emplace_back(id);
		id->Entry();

		id->RegisterChildren();
	}
	plansChilds.clear();*/
	for (auto it = plansChilds.begin(); it != plansChilds.end();)
	{
		childs.emplace_back(*it);
		(*it)->Entry();
		(*it)->RegisterChildren();
		it = plansChilds.erase(it);
	}
}
void CEntity::KillChildren()
{
	for (auto id = childs.begin(); id != childs.end();)
	{
		//if (CEntity::GetStateCount(*id) == KL_ENTITY_KILL)
		if ((*id)->state == EState::KILL)
		{
			delete *id;
			id = childs.erase(id);
		}
		else
		{
			//Ä‹N‚ÅŽq‚ÌŽq‚ðíœ‚·‚é
			(*id)->KillChildren();
			++id;
		}
	}
}
void CEntity::SetChildren(CEntity* child)
{
	plansChilds.emplace_back(child);
	child->parent = this;
}
void CEntity::Destroy(CEntity* entity)
{
	entity->Destroy();
}
void CEntity::Update(CEntity* entity)
{
	if (entity->active)
	{
		entity->Update();
	}
}
void CEntity::Entry(CEntity* entity)
{
	entity->Entry();
}
void CEntity::ChildrenUpdate(CEntity* entity)
{
	for (auto id : entity->childs)
	{
		if (id->active)
		{
			CEntity::Update(id);
			CEntity::ChildrenUpdate(id);
		}
	}
}
void CEntity::ChildrenStateAdaptation(CEntity* entity)
{
	//íœ—\’è‚ðíœ
	entity->KillChildren();
	//“o˜^—\’è‚ð“o˜^
	entity->RegisterChildren();
}
size_t CEntity::ChildCount() const
{
	return childs.size();
}
CEntity* CEntity::GetChild(const size_t index)
{
	return childs[index];
}
std::vector<CEntity*>* CEntity::GetChilds()
{
	return &childs;
}

CEntity * CEntity::GetChildren(CEntity * inEntity, const CStrID & tag)
{
	for (auto& it : inEntity->childs)
	{
		if (it->tag == tag)
		{
			return it;
		}
	}
	return nullptr;
}

CEntity * CEntity::GetChildren(CEntity * inEntity, const ELayer layer)
{
	for (auto& it : inEntity->childs)
	{
		if (it->layer == layer)
		{
			return it;
		}
	}
	return nullptr;
}

CEntity * CEntity::GetChildrenAll(CEntity * inEntity, const CStrID & tag)
{
	for (auto&it : inEntity->childs)
	{
		if (it->tag == tag)
		{
			return it;
		}
		CEntity* Return = GetChildrenAll(it, tag);
		if (Return != nullptr)
		{
			return Return;
		}
	}
	return nullptr;
}

CEntity * CEntity::GetChildrenAll(CEntity * inEntity, const ELayer layer)
{
	for (auto&it : inEntity->childs)
	{
		if (it->layer == layer)
		{
			return it;
		}
		CEntity* Return = GetChildrenAll(it, layer);
		if (Return != nullptr)
		{
			return Return;
		}
	}
	return nullptr;
}

void CEntity::GetChildrens(CEntity * inEntity, const CStrID & tag, std::vector<CEntity*>* out)
{
	for (auto& it : inEntity->childs)
	{
		if (it->tag == tag)
		{
			out->emplace_back(it);
		}
	}
}

void CEntity::GetChildrens(CEntity * inEntity, const ELayer layer, std::vector<CEntity*>* out)
{
	for (auto& it : inEntity->childs)
	{
		if (it->layer == layer)
		{
			out->emplace_back(it);
		}
	}
}

void CEntity::GetChildrensAll(CEntity * inEntity, const CStrID & tag, std::vector<CEntity*>* out)
{
	for (auto& it : inEntity->childs)
	{
		if (it->tag == tag)
		{
			out->emplace_back(it);
		}
		GetChildrensAll(it, tag, out);
	}
}

void CEntity::GetChildrensAll(CEntity * inEntity, const ELayer layer, std::vector<CEntity*>* out)
{
	for (auto& it : inEntity->childs)
	{
		if (it->layer == layer)
		{
			out->emplace_back(it);
		}
		GetChildrensAll(it, layer, out);
	}
}
