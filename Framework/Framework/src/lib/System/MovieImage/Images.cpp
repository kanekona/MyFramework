#include "Images.h"

Images::Images()
{
	preTime = 0.0f;
}
Images::Images(const std::string& path, const format& movie)
{
	preTime = 0.0f;
	Load(path, movie);
}
Images::~Images()
{

}
bool Images::Load(const std::string& path, const format& movie)
{
	CV_Open(path + movie);
	return true;
}
void Images::Enter()
{
	time.Start();
}
void Images::Update()
{
	if (!enablePlay)
	{
		return;
	}
	CV_SetFrame(videoFramerate*GetTime());
	SetMatToTexture();
}
void Images::Play()
{
	time.Pause(false);
}
void Images::Pause()
{
	time.Pause(true);
}
void Images::SetTime(const float t)
{
	time.InitTime(t);
	time.Start();
}
float Images::GetTime()
{
	return preTime + (time.GetTime() * magnification);
}
void Images::SetSpeed(const float speed)
{
	preTime += time.GetTime()*magnification;
	__super::SetSpeed(speed);
	time.Reset();
}