#include "glTimer.h"

CTime::CTime()
{
	Init();
}

CTime::~CTime()
{

}

void CTime::Init()
{
	InitNumber();
	isPlay = false;
	behavior = false;
}

void  CTime::InitNumber()
{
	initTime = 0.0f;
	nowTime = 0.0f;
	saveTime = 0.0f;
	addTime = 0.0f;
}

void CTime::Start()
{
	if (!isPlay && !behavior) {
		initTime = (float)glfwGetTime() + addTime;
		isPlay = true;
		behavior = true;
	}
}

void CTime::Stop()
{
	if (isPlay && behavior) {
		Init();
	}
}

void CTime::Pause(const bool isPause)
{
	if (behavior) {
		if (isPlay != isPause)
		{
			if (isPause)
			{
				//àÍéûí‚é~
				nowTime = (float)glfwGetTime() - initTime;
				saveTime = nowTime;
			}
			else
			{
				//å≥ÇÃà íuÇ©ÇÁçƒÇ—äJén
				initTime = (float)glfwGetTime() - saveTime;
				saveTime = 0.0f;
			}
		}
		isPlay = !isPause;
	}
}

float CTime::GetTime()
{
	if (!behavior) { return 0.0f; }
	if (isPlay) {
		nowTime = (float)glfwGetTime() - initTime;
	}
	return nowTime;
}

void CTime::InitTime(const float time_)
{
	addTime = time_;
}

bool CTime::IsPlay() const
{
	return isPlay;
}

void CTime::Reset(const float time)
{
	InitNumber();
	InitTime(time);
}