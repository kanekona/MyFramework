#include "MovieImage.h"
#include "Engine\Framework.h"
#include "Texture\Texture.h"
CMovieImage::CMovieImage()
	:CSprite(true)
{
	Init();
}
CMovieImage::~CMovieImage()
{
	Delete();
}
void CMovieImage::CV_Open(const std::string& path)
{
	if (!videoCapture.open(path))
	{
		return;
	}
	videoFramerate = static_cast<float>(videoCapture.get(CV_CAP_PROP_FPS));
	videoCapture >> mat;
	if (!texture)
	{
		texture = new CTexture();
	}
	texture->Load(mat);
}
void CMovieImage::CV_SetFrame(const float frame)
{
	videoCapture.set(CV_CAP_PROP_POS_FRAMES, frame);
}
bool CMovieImage::SetMatToTexture()
{
	videoCapture >> mat;
	if (!mat.empty())
	{
		texture->Load(mat);
		return true;
	}
	return false;
}
void CMovieImage::Init()
{
	preEnablePlay = enablePlay = true;
	loop = false;
	transform = new CTransform();
	transform->position = CFramework::Get()->GetPosition(2, 2, 3);
	transform->scale = CFramework::Get()->GetSize(1, 1);
	color = &CColor::one;
	magnification = 1.0f;
}
void CMovieImage::Delete()
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
void CMovieImage::SetPlay(const bool isPlay)
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
void CMovieImage::Play()
{

}
void CMovieImage::Pause()
{

}
void CMovieImage::SetSpeed(const float speed)
{
	magnification = speed;
}
void CMovieImage::SetTime(const float time)
{
	CV_SetFrame(time * videoFramerate);
}
void CMovieImage::EnableLoop(const bool isLoop)
{
	enablePlay = isLoop;
}
float CMovieImage::GetSpeed() const
{
	return magnification;
}