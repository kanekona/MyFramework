#include "glTimer.h"

Time::Time()
{
	Init();
}

Time::~Time()
{

}

void Time::Init()
{
	InitNumber();
	isPlay = false;
	behavior = false;
}

void  Time::InitNumber()
{
	initTime = 0.0f;
	nowTime = 0.0f;
	saveTime = 0.0f;
	addTime = 0.0f;
}

void Time::Start()
{
	if (!isPlay && !behavior) {
		initTime = (float)glfwGetTime() + addTime;
		isPlay = true;
		behavior = true;
	}
}

void Time::Stop()
{
	if (isPlay && behavior) {
		Init();
	}
}

void Time::Pause(const bool isPause)
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

float Time::GetTime()
{
	if (!behavior) { return 0.0f; }
	if (isPlay) {
		nowTime = (float)glfwGetTime() - initTime;
	}
	return nowTime;
}

void Time::InitTime(const float time_)
{
	addTime = time_;
}

bool Time::IsPlay() const
{
	return isPlay;
}

void Time::Reset(const float time)
{
	InitNumber();
	InitTime(time);
}