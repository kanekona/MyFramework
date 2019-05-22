#include "Video.h"
#include "Engine\Framework.h"
#include "Engine\OGF.hpp"
Video::Video()
{
}
Video::Video(const std::string& filePath, const format& movie, const format& sound)
{
	Load(filePath, movie, sound);
}
Video::~Video()
{
}
bool Video::Load(const std::string& filepath, const format& movie, const format& s)
{
	CV_Open(filepath + movie);
	LoadSound(filepath + s);
	return true;
}
void Video::LoadSound(const std::string& filePath)
{
	sound.Create(filePath);
}
void Video::Enter()
{
	sound.Play();
}
void Video::Update()
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
void Video::SetVolume(const float volume)
{
	sound.Volume(volume);
}
void Video::SetSpeed(const float speed)
{
	__super::SetSpeed(speed);
	sound.Pitch(magnification);
}
void Video::SetTime(const float time)
{
	sound.Skip(time);
}
float Video::GetTime() const
{
	return sound.CurrentTime();
}
void Video::Play()
{
	sound.Play();
}
void Video::Pause()
{
	sound.Pause();
}
const format MovieFormat::MP3 = ".mp3";
const format MovieFormat::MP4 = ".mp4";
const format MovieFormat::AVI = ".avi";
const format MovieFormat::WAV = ".wav";