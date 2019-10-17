#include "Images.h"

CImages::CImages()
{
	preTime = 0.0f;
}
CImages::CImages(const std::string& path, const TFormat& movie)
{
	preTime = 0.0f;
	Load(path, movie);
}
CImages::~CImages()
{

}
bool CImages::Load(const std::string& path, const TFormat& movie)
{
	CV_Open(path + movie);
	return true;
}
void CImages::Entry()
{
	time.Start();
}
void CImages::Update()
{
	if (!enablePlay)
	{
		return;
	}
	CV_SetFrame(videoFramerate*GetTime());
	SetMatToTexture();
}
void CImages::Play()
{
	time.Pause(false);
}
void CImages::Pause()
{
	time.Pause(true);
}
void CImages::SetTime(const float t)
{
	time.InitTime(t);
	time.Start();
}
float CImages::GetTime()
{
	return preTime + (time.GetTime() * magnification);
}
void CImages::SetSpeed(const float speed)
{
	preTime += time.GetTime()*magnification;
	__super::SetSpeed(speed);
	time.Reset();
}