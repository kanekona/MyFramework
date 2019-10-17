#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <unordered_map>

class CStateParam;
class CStateManager;

class CStateParam
{
	unsigned int timeCnt;
	const unsigned int id;
public:
	explicit CStateParam(const unsigned int id);
	virtual void Entry(CStateManager* manager) = 0;
	virtual void Exit(CStateManager* manager) = 0;
	virtual void Update() = 0;
	virtual bool ChangeState(CStateManager* manager) = 0;
	unsigned int GetTime() const;
	void TimeUp(const unsigned int cnt);
	void ResetTime();
	unsigned int GetID() const;
};

class CStateManager : private CNonCopyable
{
	std::unordered_map<unsigned int, CStateParam*> list;
	unsigned int nowState;
	unsigned int nextState;
	unsigned int preState;
public:
	explicit CStateManager(const unsigned int id, CStateParam* state);
	virtual ~CStateManager();
	CStateParam* GetState(const unsigned int id);
	bool SetState(const unsigned int id, CStateParam* state);
	template <class T> T* GetState(const unsigned int id)
	{
		return (T*)list[id];
	}
	void NextState(const unsigned int id);
	void Update();
	void ChangeState(const unsigned int id);
	void ChangeState();
};