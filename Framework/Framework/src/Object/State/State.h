#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <unordered_map>

class StateParam;
class StateManager;

class StateParam
{
	unsigned int timeCnt;
	const unsigned int id;
public:
	explicit StateParam(const unsigned int id);
	virtual void Enter(StateManager* manager) = 0;
	virtual void Exit(StateManager* manager) = 0;
	virtual void Update() = 0;
	virtual bool ChangeState(StateManager* manager) = 0;
	unsigned int GetTime() const;
	void TimeUp(const unsigned int cnt);
	void ResetTime();
	unsigned int GetID() const;
};

class StateManager : private NonCopyable
{
	std::unordered_map<unsigned int, StateParam*> list;
	unsigned int nowState;
	unsigned int nextState;
	unsigned int preState;
public:
	explicit StateManager(const unsigned int id, StateParam* state);
	virtual ~StateManager();
	StateParam* GetState(const unsigned int id);
	bool SetState(const unsigned int id, StateParam* state);
	template <class T> T* GetState(const unsigned int id)
	{
		return (T*)this->list[tag];
	}
	void NextState(const unsigned int id);
	void Update();
	void ChangeState(const unsigned int id);
	void ChangeState();
};