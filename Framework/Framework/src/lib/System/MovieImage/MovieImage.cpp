#include "MovieImage.h"
#include "Engine\Framework.h"
MovieImage::MovieImage()
	:Sprite(true)
{
	Init();
}
MovieImage::~MovieImage()
{
	Delete();
}
void MovieImage::CV_Open(const std::string& path)
{
	if (!videoCapture.open(path))
	{
		return;
	}
	videoFramerate = static_cast<float>(videoCapture.get(CV_CAP_PROP_FPS));
	videoCapture >> mat;
	if (!texture)
	{
		texture = new Texture();
	}
	texture->Load(mat);
}
void MovieImage::CV_SetFrame(const float frame)
{
	videoCapture.set(CV_CAP_PROP_POS_FRAMES, frame);
}
bool MovieImage::SetMatToTexture()
{
	videoCapture >> mat;
	if (!mat.empty())
	{
		texture->Load(mat);
		return true;
	}
	return false;
}
void MovieImage::Init()
{
	preEnablePlay = enablePlay = true;
	loop = false;
	transform = new Transform();
	transform->position = Framework::Get()->GetPosition(2, 2, 3);
	transform->scale = Framework::Get()->GetSize(1, 1);
	color = &Color::one;
	magnification = 1.0f;
}
void MovieImage::Delete()
{
	if (texture)
	{
		delete texture;
		texture = nullptr;
	}
	if (transform)
	{
		delete transform;
		transform = nullptr;
	}
}
void MovieImage::SetPlay(const bool isPlay)
{
	enablePlay = isPlay;
	if (enablePlay && !preEnablePlay)
	{
		//ìÆÇ´èoÇ∑
		Play();
	}
	else if (!enablePlay && preEnablePlay)
	{
		//é~Ç‹ÇÈ
		Pause();
	}
	preEnablePlay = enablePlay;
}
void MovieImage::Play()
{

}
void MovieImage::Pause()
{

}
void MovieImage::SetSpeed(const float speed)
{
	magnification = speed;
}
void MovieImage::SetTime(const float time)
{
	CV_SetFrame(time * videoFramerate);
}
void MovieImage::EnableLoop(const bool isLoop)
{
	enablePlay = isLoop;
}
float MovieImage::GetSpeed() const
{
	return magnification;
}