#include "Video.h"
#include "Engine\Framework.h"
#include "Engine\OGF.hpp"
CVideo::CVideo()
{
}
CVideo::CVideo(const std::string& filePath, const TFormat& movie, const TFormat& sound)
{
	Load(filePath, movie, sound);
}
CVideo::~CVideo()
{
}
bool CVideo::Load(const std::string& filepath, const TFormat& movie, const TFormat& s)
{
	CV_Open(filepath + movie);
	LoadSound(filepath + s);
	return true;
}
void CVideo::LoadSound(const std::string& filePath)
{
	sound.Create(filePath);
}
void CVideo::Entry()
{
	sound.Play();
}
void CVideo::Update()
{
	if (!enablePlay)
	{
		return;
	}
	CV_SetFrame(videoFramerate*sound.CurrentTime());
	SetMatToTexture();
}
//void Video::AlignMovieWithFPS()
//{
//	//フレーム数から更新フレームを計算する
//	//if (fps->FrameCheck())
//	//{
//	//	videoCapture >> mat;
//	//	//動画データがあればTextureを生成する
//	//	if (!mat.empty())
//	//	{
//	//		__super::texture->Load(mat);
//	//	}
//	//	else
//	//	{
//	//		//これでループさせてる
//	//		if (loop)
//	//		{
//	//			videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0.0);
//	//		}
//	//		else
//	//		{
//	//			enablePlay = false;
//	//			delete fps;
//	//			fps = nullptr;
//	//			sound.Stop();
//	//		}
//	//	}
//	//}
//}
void CVideo::SetVolume(const float volume)
{
	sound.Volume(volume);
}
void CVideo::SetSpeed(const float speed)
{
	__super::SetSpeed(speed);
	sound.Pitch(magnification);
}
void CVideo::SetTime(const float time)
{
	sound.Skip(time);
}
float CVideo::GetTime() const
{
	return sound.CurrentTime();
}
void CVideo::Play()
{
	sound.Play();
}
void CVideo::Pause()
{
	sound.Pause();
}
const TFormat CMovieFormat::MP3 = ".mp3";
const TFormat CMovieFormat::MP4 = ".mp4";
const TFormat CMovieFormat::AVI = ".avi";
const TFormat CMovieFormat::WAV = ".wav";