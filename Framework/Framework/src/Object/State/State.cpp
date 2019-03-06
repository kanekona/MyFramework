#include "State.h"
StateParam::StateParam(const unsigned int i)
	:id(i)
{

}
unsigned int StateParam::GetTime() const
{
	return this->timeCnt;
}
void StateParam::TimeUp(const unsigned int cnt)
{
	this->timeCnt += cnt;
}
void StateParam::ResetTime()
{
	this->timeCnt = 0;
}
unsigned int StateParam::GetID() const
{
	return this->id;
}

StateManager::StateManager(const unsigned int i, StateParam* state)
{
	this->list[i] = state;
	this->nowState = i;
	this->list[i]->Enter(this);
}

StateManager::~StateManager()
{
	auto id = this->list.begin();
	while (id != this->list.end())
	{
		delete id->second;
		id = this->list.erase(id);
	}
}

StateParam* StateManager::GetState(const unsigned int i)
{
	return this->list[i];
}
bool StateManager::SetState(const unsigned int i, StateParam* state)
{
	this->list[i] = state;
	return true;
}
void StateManager::NextState(const unsigned int i)
{
	this->nextState = i;
}
void StateManager::Update()
{
	//this->Param(this->list[this->nowState]->Param());
	while(this->list[this->nowState]->ChangeState(this))
	{
		this->ChangeState();
	}
	this->list[this->nowState]->Update();
}
void StateManager::ChangeState(const unsigned int i)
{
	this->preState = this->nowState;
	this->list[this->preState]->Exit(this);
	this->nowState = i;
	this->list[this->nowState]->Enter(this);
}
void StateManager::ChangeState()
{
	this->list[this->nowState]->Exit(this);
	this->preState = this->nowState;
	this->nowState = this->nextState;
	this->list[this->nowState]->Enter(this);
}