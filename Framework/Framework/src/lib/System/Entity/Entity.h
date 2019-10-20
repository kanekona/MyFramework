#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <vector>
#include <string>
#include "Engine\EngineTypedef.h"
#include "EntityLayer.h"
#include "StrID\StrID.h"
/**
*@brief äÓëbclass
*ï`âÊÇ∆çXêVÇÃã@î\ÇÃÇ›
*/
class CEntity : private CNonCopyable
{
public:
	enum class EState : uint8
	{
		NORMAL,
		KILL,
	};

	//! tag
	CStrID tag;
	//! Layer
	ELayer layer;
private:
	//! Enable Active
	bool active;
	//! Entity State
	EState state;
	//! Children
	std::vector<CEntity*> childs;
	//! Plans Children
	std::vector<CEntity*> plansChilds;
	//! Parent Entity
	CEntity* parent;

public:
	/**
	*@brief	constructor
	*/
	explicit CEntity();
	/**
	*@brief	destructor
	*/
	virtual ~CEntity();
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
	*@brief Get Entity State
	*@return EState Entity State
	*/
	EState GetState() const;
	/**
	*@brief	This Entity Children to Registration
	*@param[in] Entity* child Children
	*/
	void SetChildren(CEntity* child);
	/**
	*@brief	Entity Update
	*@param[in] Entity* entity this
	*/
	static void Update(CEntity* entity);
	/**
	*@brief	Entity Entry
	*@param[in] Entity* entity this
	*/
	static void Entry(CEntity* entity);
	/**
	*@brief	Entity Children Update
	*@parma[in] Entity* entity this
	*/
	static void ChildrenUpdate(CEntity* entity);
	/**
	*@brief	Entity Children Kill Check
	*@param[in] Entity* entity this
	*/
	static void ChildrenStateAdaptation(CEntity* entity);
	/**
	*@brief	Entity Delete
	*/
	void Destroy();
private:

	/**
	*@brief Entity Update
	*/
	virtual void Update();
	/**
	*@brief Entity System Entry
	*/
	virtual void Entry();
	/**
	*@brief	Register registration schedule
	*/
	void RegisterChildren();
	/**
	*@brief Kill Check Children
	*/
	void KillChildren();

public:
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
	CEntity* GetChild(const size_t index);
	/**
	*@brief Get Childrens
	*@return std::vector<Entity*>* All Children
	*/
	std::vector<CEntity*>* GetChilds();
	/**
	*@brief	Get Children
	*@tparam T assignment class
	*@return T* assignment class Children
	*@detail ë∂ç›ÇµÇ»Ç¢èÍçáÇÕnullptrÇï‘Ç∑
	*@detail ìoò^ÇµÇƒÇ¢ÇÈÇ‡ÇÃÇ∆ìoò^ó\íËÇÃÇ‡ÇÃÇ©ÇÁåüçıÇ∑ÇÈ
	*/
	template <class T> CEntity* GetChild()
	{
		return CEntity::GetChildren<T>(this);
	}
	template <class T> CEntity* GetChildAll()
	{
		return CEntity::GetChildrenAll<T>(this);
	}
	CEntity* GetChild(const CStrID& inTag)
	{
		return CEntity::GetChildren(this, inTag);
	}
	CEntity* GetChildAll(const CStrID& inTag)
	{
		return CEntity::GetChildrenAll(this, inTag);
	}
	CEntity* GetChild(const ELayer& inLayer)
	{
		return CEntity::GetChildren(this, inLayer);
	}
	CEntity* GetChildAll(const ELayer& inLayer)
	{
		return CEntity::GetChildrenAll(this, inLayer);
	}
	template <class T> void GetChilds(std::vector<CEntity*>* out)
	{
		GetChildrens<T>(this, out);
	}
	template <class T> void GetChildsAll(std::vector<CEntity*>* out)
	{
		GetChildrensAll(this, out);
	}
	void GetChilds(const CStrID& inTag, std::vector<CEntity*>* out)
	{
		GetChildrens(this, inTag, out);
	}
	void GetChildsAll(const CStrID& inTag, std::vector<CEntity*>* out)
	{
		GetChildrensAll(this, inTag, out);
	}
	void GetChilds(const ELayer& inLayer, std::vector<CEntity*>* out)
	{
		GetChildrens(this, inLayer, out);
	}
	void GetChildsAll(const ELayer& inLayer, std::vector<CEntity*>* out)
	{
		GetChildrensAll(this, inLayer, out);
	}
private:
	template <class T> static CEntity* GetChildren(CEntity* inEntity)
	{
		for (auto& it : inEntity->childs)
		{
			if (typeid(*it) == typeid(T))
			{
				return it;
			}
		}
		return nullptr;
	}
	static CEntity* GetChildren(CEntity* inEntity, const CStrID& tag);
	static CEntity* GetChildren(CEntity* inEntity, const ELayer layer);
	template <class T> static CEntity* GetChildrenAll(CEntity* inEntity)	
	{
		for (auto&it : inEntity->childs)
		{
			if (typeid(*it) == typeid(T))
			{
				return it;
			}
			CEntity* Return = GetChildrenAll<T>(it);
			if (Return != nullptr)
			{
				return Return;
			}
		}
		return nullptr;
	}
	static CEntity* GetChildrenAll(CEntity* inEntity, const CStrID& tag);
	static CEntity* GetChildrenAll(CEntity* inEntity, const ELayer layer);
	template <class T> static void GetChildrens(CEntity* inEntity, std::vector<CEntity*>* out)
	{
		for (auto& it : inEntity->childs)
		{
			if (typeid(*it) == typeid(T))
			{
				out->emplace_back(it);
			}
		}
	}
	static void GetChildrens(CEntity* inEntity, const CStrID& tag, std::vector<CEntity*>* out);
	static void GetChildrens(CEntity* inEntity, const ELayer layer, std::vector<CEntity*>* out);
	template <class T> static void GetChildrensAll(CEntity* inEntity, std::vector<CEntity*>* out)
	{
		for (auto& it : inEntity->childs)
		{
			if (typeid(*it) == typeid(T))
			{
				out->emplace_back(it);
			}
			GetChildrensAll<T>(it);
		}
	}
	static void GetChildrensAll(CEntity* inEntity, const CStrID& tag, std::vector<CEntity*>* out);
	static void GetChildrensAll(CEntity* inEntity, const ELayer layer, std::vector<CEntity*>* out);
};