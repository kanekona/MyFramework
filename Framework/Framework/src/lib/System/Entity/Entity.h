#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <vector>
#include <string>
#include "EntityLayer.h"
#define KL_ENTITY_NORMAL 0x00
#define KL_ENTITY_KILL 0x01
/**
*@brief Šî‘bclass
*•`‰æ‚ÆXV‚Ì‹@”\‚Ì‚İ
*/
class Entity : private NonCopyable
{
	//! Enable Active
	bool active;
	//! Entity StateCount
	unsigned int stateCount;
	//! Children
	std::vector<Entity*> childs;
	//! Plans Children
	std::vector<Entity*> plansChilds;
	/**
	*@brief Entity Update
	*/
	virtual void Update();
	/**
	*@brief Entity System Enter
	*/
	virtual void Enter();
	/**
	*@brief	Register registration schedule
	*/
	void RegisterChildren();
	/**
	*@brief Kill Check Children
	*/
	void KillChildren();
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@return T* assigment class
	*/
	template <class T> static T* GetChildren(std::vector<Entity*>* entity)
	{
		for (auto it : *entity)
		{
			if ((typeid(*it) == typeid(T)))
			{
				return static_cast<T*>(it);
			}
			T* t = GetChildren<T>(&it->childs);
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@param[in] std::string tag Entity Tag
	*@return T* assigment class
	*/
	template <class T> static T* GetChildren(std::vector<Entity*>* entity,const std::string& tag)
	{
		for (auto it : *entity)
		{
			if (it->tag == tag)
			{
				return static_cast<T*>(it);
			}
			T* t = GetChildren<T>(&it->childs, tag);
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@param[in] Layer layer Entity Layer
	*@return T* assigment class
	*/
	template <class T> static T* GetChildren(std::vector<Entity*>* entity,const Layer& layer)
	{
		for (auto it : *entity)
		{
			if (it->layer == layer)
			{
				return static_cast<T*>(it);
			}
			T* t = GetChildren<T>(&it->childs, layer);
			if (t != nullptr)
			{
				return t;
			}
		}
		return nullptr;
	}
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@param[out] std::vector<T*>* vector Entitys Box
	*/
	template <class T> static void GetChildrens(std::vector<Entity*>* entity, std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if ((typeid(*it) == typeid(T)))
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			GetChildrens<T>(&it->childs, vector);
		}
	}
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@param[in] std::string tag Entity Tag
	*@param[out] std::vector<T*>* vector Entitys Box
	*/
	template <class T> static void GetChildrens(std::vector<Entity*>* entity, const std::string& tag,std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if (it->tag == tag)
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			GetChildrens<T>(&it->childs, tag, vector);
		}
	}
	/**
	*@brief	Get Children
	*@tparam T assigment class
	*@param[in] std::vector<Entity*>* entity Entity Childrens
	*@param[in] Layer layer Entity Layer0
	*@param[out] std::vector<T*>* vector Entitys Box
	*/
	template <class T> static void GetChildrens(std::vector<Entity*>* entity, const Layer& layer,std::vector<T*>* vector)
	{
		for (auto it : *entity)
		{
			if (it->layer == layer)
			{
				vector->emplace_back(static_cast<T*>(it));
			}
			GetChildrens<T>(&it->childs, layer, vector);
		}
	}
public:
	//! tag
	std::string tag;
	//! Layer
	Layer layer;
	/**
	*@brief	constructor
	*/
	explicit Entity();
	/**
	*@brief	destructor
	*/
	virtual ~Entity();
	/**
	*@brief	Entity Set Active
	*@param[in] bool isActive EntityActive
	*/
	void SetActive(const bool isActive);
	/**
	*@brief Entity GetActive
	*@return bool Entity Active
	*/
	bool GetActive() const;
	/**
	*@brief	This Entity Children to Registration
	*@param[in] Entity* child Children
	*/
	void SetChildren(Entity* child);
	/**
	*@brief Get Entity State
	*@param[in] Entity* entity this
	*@return int EntityStateCount
	*/
	static int GetStateCount(Entity* entity);
	/**
	*@brief	Entity Destroy
	*@param[in] Entity* entity this
	*/
	static void Destroy(Entity* entity);
	/**
	*@brief	Entity Update
	*@param[in] Entity* entity this
	*/
	static void Update(Entity* entity);
	/**
	*@brief	Entity Enter
	*@param[in] Entity* entity this
	*/
	static void Enter(Entity* entity);
	/**
	*@brief	Entity Children Update
	*@parma[in] Entity* entity this
	*/
	static void ChildrenUpdate(Entity* entity);
	/**
	*@brief	Entity Children Kill Check
	*@param[in] Entity* entity this
	*/
	static void ChildrenStateAdaptation(Entity* entity);
	/**
	*@brief	Entity Delete
	*/
	void Destroy();
	/**
	*@brief Get Children Count
	*@return size_t This Children Size
	*/
	size_t ChildCount() const;
	/**
	*@brief	Get Children
	*@param[in] size_t index Children Number
	*@return Entity* Children
	*/
	Entity* GetChild(const size_t index);
	/**
	*@brief Get Children
	*/
	Entity* GetChild(const Layer key);
	/**
	*@brief Get Childrens
	*@return std::vector<Entity*>* All Children
	*/
	std::vector<Entity*>* GetChilds();
	/**
	*@brief	Get Children
	*@tparam T assignment class
	*@return T* assignment class Children
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetChild()
	{
		T* t = Entity::GetChildren<T>(&this->childs);
		if (t != nullptr) {
			return t;
		}
		t = Entity::GetChildren<T>(&this->plansChilds);
		return t;
		//return Entity::GetChildren<T>(&this->childs) || Entity::GetChildren<T>(&this->plansChilds);
	}
	/**
	*@brief	Get Children
	*@tparam T assignment class
	*@param[in] std::string tag Entity Tag
	*@return T* assignment class Children
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetChild(const std::string& tag)
	{
		T* t = Entity::GetChildren<T>(&this->childs, tag);
		if (t != nullptr) {
			return t;
		}
		t = Entity::GetChildren<T>(&this->plansChilds, tag);
		return t;
		//return Entity::GetChildren<T>(&this->childs) || Entity::GetChildren<T>(&this->plansChilds);
	}
	/**
	*@brief	Get Children
	*@tparam T assignment class
	*@param[in] Layer layer Entity Layer
	*@return T* assignment class Children
	*@detail ‘¶İ‚µ‚È‚¢ê‡‚Ínullptr‚ğ•Ô‚·
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> T* GetChild(const Layer& layer)
	{
		T* t = Entity::GetChildren<T>(&this->childs, layer);
		if (t != nullptr) {
			return t;
		}
		t = Entity::GetChildren<T>(&this->plansChilds, layer);
		return t;
		//return Entity::GetChildren<T>(&this->childs) || Entity::GetChildren<T>(&this->plansChilds);
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@return std::vector<T*> assignment class Childrens
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetChilds()
	{
		std::vector<T*> vector;
		Entity::GetChildrens<T>(&this->childs, &vector);
		Entity::GetChildrens<T>(&this->plansChilds, &vector);
		return vector;
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@param[in] std::string tag Entity Tag
	*@return std::vector<T*> assignment class Childrens
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetChilds(const std::string& tag)
	{
		std::vector<T*> vector;
		Entity::GetChildrens<T>(&this->childs, tag, &vector);
		Entity::GetChildrens<T>(&this->plansChilds, tag, &vector);
		return vector;
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@param[in] Layer layer Entity Layer
	*@return std::vector<T*> assignment class Childrens
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> std::vector<T*> GetChilds(const Layer& layer)
	{
		std::vector<T*> vector;
		Entity::GetChildrens<T>(&this->childs, layer, &vector);
		Entity::GetChildrens<T>(&this->plansChilds, layer, &vector);
		return vector;
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@param[out] std::vector<T*>* vector Entity Box
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> void GetChilds(std::vector<T*>* vector)
	{
		Entity::GetChildrens<T>(&this->childs, vector);
		Entity::GetChildrens<T>(&this->plansChilds, vector);
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@param[in] std::string tag Entity Tag
	*@param[out] std::vector<T*>* vector Entity Box
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> void GetChilds(const std::string& tag, std::vector<T*>* vector)
	{
		Entity::GetChildrens<T>(&this->childs, tag, vector);
		Entity::GetChildrens<T>(&this->plansChilds, tag, vector);
	}
	/**
	*@brief	Get Childrens
	*@tparam T assignment class
	*@param[in] Layer layer Entity Layer
	*@param[out] std::vector<T*>* vector Entity Box
	*@detail “o˜^‚µ‚Ä‚¢‚é‚à‚Ì‚Æ“o˜^—\’è‚Ì‚à‚Ì‚©‚çŒŸõ‚·‚é
	*/
	template <class T> void GetChilds(const Layer& layer, std::vector<T*>* vector)
	{
		Entity::GetChildrens<T>(&this->childs, layer, vector);
		Entity::GetChildrens<T>(&this->plansChilds, layer, vector);
	}
};