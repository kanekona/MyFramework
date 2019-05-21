#include "Video.h"
#include "Engine\Framework.h"
#include "Engine\OGF.hpp"
Video::Video()
	:Sprite(true)
{
	Init();
}
Video::Video(const std::string& filePath, const format& movie, const format& sound)
	:Sprite(true)
{
	Init();
	Load(filePath, movie, sound);
}
Video::~Video()
{
	delete __super::texture;
	delete transform;
}
void Video::Init()
{
	preEnablePlay = enablePlay = true;
	loop = true;
	transform = new Transform();
	transform->position = Framework::Get()->GetPosition(2, 2, 3);
	transform->scale = Framework::Get()->GetSize(1, 1);
	color = &Color::one;
	magnification = 1.0f;
	tag = "MovieImage";
}
bool Video::Load(const std::string& filepath, const format& movie, const format& s)
{
	//Open���Ă���ꍇ���ēǂݍ���
	if (!this->videoCapture.open(filepath + movie))
	{
		KL::OutDebugData("log.txt", "MovieLoadError");
		return false;
	}
	//����̃t���[�����[�g�̎擾
	videoFramerate = static_cast<float>(videoCapture.get(CV_CAP_PROP_FPS));
	//1frame�ڂ��s��ɓn��
	videoCapture >> mat;
	//�s��f�[�^����Texture�f�[�^�𐶐�
	__super::texture = new Texture();
	__super::texture->Load(mat);
	SoundLoad(filepath + s);
	return true;
}
void Video::SoundLoad(const std::string& filePath)
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
	MatchMovieAndSound();
}
void Video::MatchMovieAndSound()
{
	//�T�E���h�̎��Ԃ���t���[�����w�肵�ĉ�ʂɏo��
	videoCapture.set(CV_CAP_PROP_POS_FRAMES, videoFramerate*sound.CurrentTime());
	videoCapture >> mat;
	if (!mat.empty())
	{
		texture->Load(mat);
	}
}
void Video::AlignMovieWithFPS()
{
	//�t���[��������X�V�t���[�����v�Z����
	//if (fps->FrameCheck())
	//{
	//	videoCapture >> mat;
	//	//����f�[�^�������Texture�𐶐�����
	//	if (!mat.empty())
	//	{
	//		__super::texture->Load(mat);
	//	}
	//	else
	//	{
	//		//����Ń��[�v�����Ă�
	//		if (loop)
	//		{
	//			videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0.0);
	//		}
	//		else
	//		{
	//			enablePlay = false;
	//			delete fps;
	//			fps = nullptr;
	//			sound.Stop();
	//		}
	//	}
	//}
}
void Video::EnableLoop(const bool isLoop)
{
	loop = isLoop;
}
void Video::SetPlay(const bool isPlay)
{
	enablePlay = isPlay;
	if (enablePlay && !preEnablePlay)
	{
		//�����o��
		SetSpeed();
		sound.Play();
	}
	else if(!enablePlay && preEnablePlay)
	{
		//�~�܂�
		sound.Pause();
	}
	preEnablePlay = enablePlay;
}
void Video::SetVolume(const float volume)
{
	sound.Volume(volume);
}
void Video::Speed(const float value)
{
	magnification = value;
	SetSpeed();
}
void Video::SetSpeed()
{
	sound.Pitch(magnification);
}
float Video::GetSpeed() const
{
	return magnification;
}
void Video::SetTime(const float time)
{
	sound.Skip(time);
}
float Video::GetTime() const
{
	return sound.CurrentTime();
}
const format MovieFormat::MP3 = ".mp3";
const format MovieFormat::MP4 = ".mp4";
const format MovieFormat::AVI = ".avi";
const format MovieFormat::WAV = ".wav";