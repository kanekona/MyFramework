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
	//Openしている場合閉じて読み込む
	if (!this->videoCapture.open(filepath + movie))
	{
		KL::OutDebugData("log.txt", "MovieLoadError");
		return false;
	}
	//動画のフレームレートの取得
	this->videoFramerate = (float)videoCapture.get(CV_CAP_PROP_FPS);
	//1frame目を行列に渡す
	videoCapture >> mat;
	//行列データからTextureデータを生成
	__super::texture = new Texture();
	__super::texture->Load(mat);
	//更新速度を指定する
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
	//フレーム数から更新フレームを計算する
	if (fps->FrameCheck())
	{
		videoCapture >> mat;
		//動画データがあればTextureを生成する
		if (!mat.empty())
		{
			__super::texture->Load(mat);
		}
		else
		{
			//これでループさせてる
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
		//動き出す
		fps = new FPS();
		fps->SetFrameRate(this->videoFramerate);
		sound->Play();
	}
	else if(!enablePlay && preEnablePlay)
	{
		//止まる
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