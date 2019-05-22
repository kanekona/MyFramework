#include "Images.h"

Images::Images()
{

}
Images::Images(const std::string& path, const format& movie)
{
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
	CV_SetFrame(videoFramerate*time.GetTime() * magnification);
	SetMatToTexture();
}
void Images::Play()
{
	time.Pause();
}
void Images::Pause()
{
	time.Pause();
}
void Images::SetTime(const float t)
{
	time.InitTime(t);
	time.Start();
}
float Images::GetTime()
{
	return time.GetTime() * magnification;
}