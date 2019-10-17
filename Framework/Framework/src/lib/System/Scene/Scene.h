#pragma once
#include "Engine\EngineMacro.h"
#include "Entity\Entity.h"
#include "RenderingManager\RenderingManager.h"
#include "Camera\Camera.h"
#include <typeinfo>
class CScene : private CNonCopyable
{
	//! AllEntity
	std::vector<CEntity*> entitys;
	//! Plans Entity
	std::vector<CEntity*> plansEntity;
	//! RenderingManager
	CRenderingManager renderingManager;
	//! MainCamera
	CCamera2D* camera;
	//! 
	/**
	*@brief	Register registration schedule
	*/
	void RegisterEntity();
	/**
	*@brief	Kill Plans Kills
	*/
	void KillEntity();
public:
	//! tag
	CStrID tag;
	/**
	*@brief constructor
	*/
	explicit CScene();
	/**
	*@brief	destructor
	*/
	virtual ~CScene();
	/**
	*@brief Scene Entry
	*/
	virtual void Entry();
	/**
	*@brief	Registration Entity
	*/
	void SetEntity(CEntity* entity);
	/**
	*@brief	Get RenderingManager
	*@return RenderingManager* this RenderingManager
	*/
	CRenderingManager* GetRenderingManager();
	/**
	*@brief	Get Camera
	*@return Camera2D* template Scene Camera
	*/
	CCamera2D* GetCamera();
	/**
	*@brief	Get Entity Count
	*@return size_t This Entity Size
	*/
	size_t EntityCount() const;
	/**
	*@brief	Get Entity
	*@param[in] size_t num Entity Number
	*@return Entity* entity
	*/
	CEntity* GetEntity(const size_t num);
	/**
	*@brief	Get Entitys
	*@return std::vector<Entity*>* All Entity
	*/
	std::vector<CEntity*>* GetEntitys();

	template <class T> CEntity* GetEntity()
	{
		for (auto& it : entitys)
		{
			if (typeid(T) == typeid(*it))
			{
				return it;
			}
		}
		return nullptr;
	}
	CEntity* GetEntity(const CStrID& inTag)
	{
		for (auto& it : entitys)
		{
			if (it->tag == inTag)
			{
				return it;
			}
		}
		return nullptr;
	}
	CEntity* GetEntity(const ELayer& inLayer)
	{
		for (auto& it : entitys)
		{
			if (it->layer == inLayer)
			{
				return it;
			}
		}
		return nullptr;
	}
	template <class T> CEntity* GetEntityAll()
	{
		for (auto& it : entitys)
		{
			if (typeid(T) == typeid(*it))
			{
				return it;
			}
			CEntity* Return = it->GetChildAll<T>();
			if (Return != nullptr)
			{
				return Return;
			}
		}
		return nullptr;
	}
	CEntity* GetEntityAll(const CStrID& inTag)
	{
		for (auto& it : entitys)
		{
			if (it->tag == inTag)
			{
				return it;
			}
			CEntity* Return = it->GetChildAll(inTag);
			if (Return != nullptr)
			{
				return Return;
			}
		}
		return nullptr;
	}
	CEntity* GetEntityAll(const ELayer& inLayer)
	{
		for (auto& it : entitys)
		{
			if (it->layer == inLayer)
			{
				return it;
			}
			CEntity* Return = it->GetChildAll(inLayer);
			if (Return != nullptr)
			{
				return Return;
			}
		}
		return nullptr;
	}
	template <class T> void GetEntitys(std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (typeid(T) == typeid(*it))
			{
				out->emplace_back(it);
			}
		}
	}
	void GetEntitys(const CStrID& inTag, std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (it->tag == inTag)
			{
				out->emplace_back(it);
			}
		}
	}
	void GetEntitys(const ELayer& inLayer, std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (it->layer == inLayer)
			{
				out->emplace_back(it);
			}
		}
	}
	template <class T> void GetEntitysAll(std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (typeid(T) == typeid(*it))
			{
				out->emplace_back(it);
			}
			it->GetChildsAll<T>(out);
		}
	}
	void GetEntitysAll(const CStrID& inTag, std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (it->tag == inTag)
			{
				out->emplace_back(it);
			}
			it->GetChildsAll(inTag, out);
		}
	}
	void GetEntitysAll(const ELayer& inLayer, std::vector<CEntity*>* out)
	{
		for (auto& it : entitys)
		{
			if (it->layer == inLayer)
			{
				out->emplace_back(it);
			}
			it->GetChildsAll(inLayer, out);
		}
	}
	/**
	*@brief	Entity State Chenge Adaptation
	*@param[in] Scene* scene this
	*/
	static void EntityStateAdaptation(CScene* scene);
	/**
	*@brief	Entitys Update
	*@param[in] Scene* scene this
	*/
	static void EntityUpdate(CScene* scene);
#if DEBUG_ENABLE
	/**
	*@brief Debug Program
	*/
	void Debug();
#endif
};