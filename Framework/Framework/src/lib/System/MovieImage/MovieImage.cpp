#include "MovieImage.h"
#include "Engine\Framework.h"
MovieImage::MovieImage()
	:Sprite(true)
{
	Init();
}
MovieImage::MovieImage(const std::string& filePath, const format& movie, const format& sound)
	:Sprite(true)
{
	Init();
	this->Load(filePath, movie, sound);
}
MovieImage::~MovieImage()
{
	delete __super::texture;
	delete sound;
	if (fps)
	{
		delete fps;
	}
	delete transform;
}
void MovieImage::Init()
{
	this->preEnablePlay = this->enablePlay = true;
	this->loop = true;
	transform = new Transform();
	transform->position = Framework::Get()->GetPosition(2, 2, 3);
	transform->scale = Framework::Get()->GetSize(1, 1);
	color = &Color::one;
	magnification = 1.0f;
}
bool MovieImage::Load(const std::string& filepath, const format& movie, const format& s)
{
	//Open���Ă���ꍇ���ēǂݍ���
	if (!this->videoCapture.open(filepath + movie))
	{
		KL::OutDebugData("log.txt", "MovieLoadError");
		return false;
	}
	//����̃t���[�����[�g�̎擾
	this->videoFramerate = (float)videoCapture.get(CV_CAP_PROP_FPS);
	//1frame�ڂ��s��ɓn��
	videoCapture >> mat;
	//�s��f�[�^����Texture�f�[�^�𐶐�
	__super::texture = new Texture();
	__super::texture->Load(mat);
	//�X�V���x���w�肷��
	fps = new FPS();
	fps->SetFrameRate(this->videoFramerate);
	SoundLoad(filepath + s);
	return true;
}
void MovieImage::SoundLoad(const std::string& filePath)
{
	sound = new Sound();
	this->sound->Create(filePath);
}
void MovieImage::Enter()
{
	sound->Play();
}
void MovieImage::Update()
{
	if (!this->enablePlay)
	{
		return;
	}
	//�t���[��������X�V�t���[�����v�Z����
	if (fps->FrameCheck())
	{
		videoCapture >> mat;
		//����f�[�^�������Texture�𐶐�����
		if (!mat.empty())
		{
			__super::texture->Load(mat);
		}
		else
		{
			//����Ń��[�v�����Ă�
			if (this->loop)
			{
				videoCapture.set(CV_CAP_PROP_POS_FRAMES, 0.0);
			}
			else
			{
				this->enablePlay = false;
				delete fps;
				fps = nullptr;
				this->sound->Stop();
			}
		}
	}
}
void MovieImage::EnableLoop(const bool isLoop)
{
	this->loop = isLoop;
}
void MovieImage::SetPlay(const bool isPlay)
{
	this->enablePlay = isPlay;
	if (enablePlay && !preEnablePlay)
	{
		//�����o��
		fps = new FPS();
		fps->SetFrameRate(this->videoFramerate);
		sound->Play();
	}
	else if(!enablePlay && preEnablePlay)
	{
		//�~�܂�
		delete fps;
		fps = nullptr;
		sound->Pause();
	}
	this->preEnablePlay = this->enablePlay;
}
void MovieImage::SetVolume(const float volume)
{
	if (sound)
	{
		this->sound->Volume(volume);
	}
}
void MovieImage::Speed(const float value)
{
	this->magnification = value;
}

const format MovieFormat::MP3 = ".mp3";
const format MovieFormat::MP4 = ".mp4";
const format MovieFormat::AVI = ".avi";
const format MovieFormat::WAV = ".wav";