#pragma once
#include "Entity\Entity.h"
#include "RenderingManager\RenderingManager.h"
#include "Camera\Camera.h"
#include <typeinfo>
class Scene : private NonCopyable
{
	//! AllEntity
	std::vector<Entity*> entitys;
	//! Plans Entity
	std::vector<Entity*> plansEntity;
	//! RenderingManager
	RenderingManager renderingManager;
	//! MainCamera
	Camera2D* camera;
	//! 
	/**
	*@brief	Register registration schedule
	*/
	void RegisterEntity();
	/**
	*@brief	Kill Plans Kills
	*/
	void KillEntity();
	/**
	*
	*/
	template <class T> static T* GetEntity(std::vector<Entity*>* entity)
	{
		for (auto it : *entity)
		{
			if ((typeid(T) == typeid(*it)))
			{
				return static_cast<T*>(it);
			}
			T* t = it->GetChild<T>();
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
	template <class T> static T* GetEntity(std::vector<Entity*>* entity,const std::string& tag)
	{
		for (auto it : *entity)
		{
			if (it->tag == tag)
			{
				return static_cast<T*>(it);
			}
			T* t = it->GetChild<T>(tag);
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
	template <class T> static T* GetEntity(std::vector<Entity*>* entity,const Layer& layer)
	{
		for (auto it : *entity)
		{
			if (it->layer == layer)
			{
				return static_cast<T*>(it);
			}
			T* t = it->GetChild<T>(layer);
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}

	template <class T> static void GetEntitys(std::vector<Entity*>* entity, std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if ((typeid(T) == typeid(*it)))
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			it->GetChilds<T>(vector);
		}
	}
	template <class T> static void GetEntitys(std::vector<Entity*>* entity, const std::string& tag, std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if (it->tag == tag)
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			it->GetChilds<T>(tag, vector);
		}
	}
	template <class T> static void GetEntitys(std::vector<Entity*>* entity, const Layer& layer, std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if (it->layer == layer)
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			it->GetChilds<T>(layer, vector);
		}
	}
public:
	//! tag
	std::string tag;
	/**
	*@brief constructor
	*/
	explicit Scene();
	/**
	*@brief	destructor
	*/
	virtual ~Scene();
	/**
	*@brief Scene Enter
	*/
	virtual void Enter();
	/**
	*@brief	Registration Entity
	*/
	void SetEntity(Entity* entity);
	/**
	*@brief	Get RenderingManager
	*@return RenderingManager* this RenderingManager
	*/
	RenderingManager* GetRenderingManager();
	/**
	*@brief	Get Camera
	*@return Camera2D* template Scene Camera
	*/
	Camera2D* GetCamera();
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
	Entity* GetEntity(const size_t num);
	/**
	*@brief	Get Entitys
	*@return std::vector<Entity*>* All Entity
	*/
	std::vector<Entity*>* GetEntitys();
	/**
	*@brief	Get Entity
	*@tparam T assignment class
	*@return T* assignment class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetEntity()
	{
		return Scene::GetEntity<T>(&this->entitys) || Scene::GetEntity<T>(&this->plansEntity);
	}
	/**
	*@brief	Get Entity
	*@tparam T Assigment Class
	*@param[in] std::string tag Assigment Tag
	*@return T* Assigment Tag Class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetEntity(const std::string& tag)
	{
		return Scene::GetEntity<T>(&this->entitys, tag) || Scene::GetEntity<T>(&this->plansEntity, tag);
	}
	/**
	*@brief	Get Entity
	*@tparam T Assigment Class
	*@param[in] std::string tag Assigment Tag
	*@return T* Assigment Tag Class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetEntity(const Layer& layer)
	{
		return Scene::GetEntity<T>(&this->entitys, layer) || Scene::GetEntity<T>(&this->plansEntity, layer);
	}
	/**
	*@brief	Get Entity
	*@tparam T assignment class
	*@return T* assignment class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetEntitys()
	{
		std::vector<T> vector;
		Scene::GetEntitys<T>(&this->entitys, &vector);
		Scene::GetEntitys<T>(&this->plansEntity, &vector);
		return vector;
	}
	/**
	*@brief	Get Entity
	*@tparam T Assigment Class
	*@param[in] std::string tag Assigment Tag
	*@return T* Assigment Tag Class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetEntitys(const std::string& tag)
	{
		std::vector<T> vector;
		Scene::GetEntitys<T>(&this->entitys, tag,&vector);
		Scene::GetEntitys<T>(&this->plansEntity, tag,&vector);
		return vector;
	}
	/**
	*@brief	Get Entity
	*@tparam T Assigment Class
	*@param[in] std::string tag Assigment Tag
	*@return T* Assigment Tag Class Entity
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetEntitys(const Layer& layer)
	{
		std::vector<T> vector;
		Scene::GetEntitys<T>(&this->entitys, layer,&vector);
		Scene::GetEntitys<T>(&this->plansEntity, layer,&vector);
		return vector;
	}
	/**
	*@brief	Entity State Chenge Adaptation
	*@param[in] Scene* scene this
	*/
	static void EntityStateAdaptation(Scene* scene);
	/**
	*@brief	Entitys Update
	*@param[in] Scene* scene this
	*/
	static void EntityUpdate(Scene* scene);
	/**
	*@brief Debug Program
	*/
	void Debug();
};