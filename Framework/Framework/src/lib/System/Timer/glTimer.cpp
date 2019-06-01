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
	this->isPlay = false;
	this->behavior = false;
}

void  Time::InitNumber()
{
	this->initTime = 0.0f;
	this->nowTime = 0.0f;
	this->saveTime = 0.0f;
	this->addTime = 0.0f;
}

void Time::Start()
{
	if (!this->isPlay && !this->behavior) {
		this->initTime = (float)glfwGetTime() + this->addTime;
		this->isPlay = true;
		this->behavior = true;
	}
}

void Time::Stop()
{
	if (this->isPlay && this->behavior) {
		Init();
	}
}

void Time::Pause(const bool isPause)
{
	if (this->behavior) {
		if (isPlay != isPause)
		{
			if (isPause)
			{
				//ˆêŽž’âŽ~
				this->nowTime = (float)glfwGetTime() - this->initTime;
				this->saveTime = this->nowTime;
			}
			else
			{
				//Œ³‚ÌˆÊ’u‚©‚çÄ‚ÑŠJŽn
				this->initTime = (float)glfwGetTime() - this->saveTime;
				this->saveTime = 0.0f;
			}
		}
		isPlay = !isPause;
	}
}

float Time::GetTime()
{
	if (!this->behavior) { return 0.0f; }
	if (this->isPlay) {
		this->nowTime = (float)glfwGetTime() - this->initTime;
	}
	return this->nowTime;
}

void Time::InitTime(const float time_)
{
	this->addTime = time_;
}

bool Time::IsPlay() const
{
	return this->isPlay;
}

void Time::Reset(const float time)
{
	InitNumber();
	InitTime(time);
}