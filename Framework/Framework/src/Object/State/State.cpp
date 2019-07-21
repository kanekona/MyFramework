#include "State.h"
StateParam::StateParam(const unsigned int i)
	:id(i)
{

}
unsigned int StateParam::GetTime() const
{
	return timeCnt;
}
void StateParam::TimeUp(const unsigned int cnt)
{
	timeCnt += cnt;
}
void StateParam::ResetTime()
{
	timeCnt = 0;
}
unsigned int StateParam::GetID() const
{
	return id;
}

StateManager::StateManager(const unsigned int i, StateParam* state)
{
	list[i] = state;
	nowState = i;
	list[i]->Enter(this);
}

StateManager::~StateManager()
{
	auto id = list.begin();
	while (id != list.end())
	{
		delete id->second;
		id = list.erase(id);
	}
}

StateParam* StateManager::GetState(const unsigned int i)
{
	return list[i];
}
bool StateManager::SetState(const unsigned int i, StateParam* state)
{
	list[i] = state;
	return true;
}
void StateManager::NextState(const unsigned int i)
{
	nextState = i;
}
void StateManager::Update()
{
	//Param(list[nowState]->Param());
	while(list[nowState]->ChangeState(this))
	{
		ChangeState();
	}
	list[nowState]->Update();
}
void StateManager::ChangeState(const unsigned int i)
{
	preState = nowState;
	list[preState]->Exit(this);
	nowState = i;
	list[nowState]->Enter(this);
}
void StateManager::ChangeState()
{
	list[nowState]->Exit(this);
	preState = nowState;
	nowState = nextState;
	list[nowState]->Enter(this);
}