#include "State.h"
CStateParam::CStateParam(const unsigned int i)
	:id(i)
{

}
unsigned int CStateParam::GetTime() const
{
	return timeCnt;
}
void CStateParam::TimeUp(const unsigned int cnt)
{
	timeCnt += cnt;
}
void CStateParam::ResetTime()
{
	timeCnt = 0;
}
unsigned int CStateParam::GetID() const
{
	return id;
}

CStateManager::CStateManager(const unsigned int i, CStateParam* state)
{
	list[i] = state;
	nowState = i;
	list[i]->Entry(this);
}

CStateManager::~CStateManager()
{
	auto id = list.begin();
	while (id != list.end())
	{
		delete id->second;
		id = list.erase(id);
	}
}

CStateParam* CStateManager::GetState(const unsigned int i)
{
	return list[i];
}
bool CStateManager::SetState(const unsigned int i, CStateParam* state)
{
	list[i] = state;
	return true;
}
void CStateManager::NextState(const unsigned int i)
{
	nextState = i;
}
void CStateManager::Update()
{
	//Param(list[nowState]->Param());
	while(list[nowState]->ChangeState(this))
	{
		ChangeState();
	}
	list[nowState]->Update();
}
void CStateManager::ChangeState(const unsigned int i)
{
	preState = nowState;
	list[preState]->Exit(this);
	nowState = i;
	list[nowState]->Entry(this);
}
void CStateManager::ChangeState()
{
	list[nowState]->Exit(this);
	preState = nowState;
	nowState = nextState;
	list[nowState]->Entry(this);
}