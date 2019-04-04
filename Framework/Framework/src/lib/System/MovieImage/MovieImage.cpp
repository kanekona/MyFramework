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
	//videoCapture >> mat;
	//行列データからTextureデータを生成
	__super::texture = new Texture();
	__super::texture->Load("./data/image/back.png");
	//更新速度を指定する
	fps = new FPS();
	fps->SetFrameRate(this->videoFramerate);
	SoundLoad(filepath + s);
	texture->LoadShader("test");
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
		//videoCapture >> mat;
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
void MovieImage::Draw()
{
	Box2D draw(Vec2(), Framework::Get()->GetSize(1, 1));
	GLfloat vtx[] = {
		draw.x,draw.h,
		draw.w,draw.h,
		draw.w,draw.y,
		draw.x,draw.y,
	};
	const GLfloat texuv[] = {
			0.f,1.f,
			1.f,1.f,
			1.f,0.f,
			0.f,0.f,
	};
	const GLfloat texcolor[] = {
		color->red,
		color->green,
		color->blue,
		color->alpha,
		color->red,
		color->green,
		color->blue,
		color->alpha,
		color->red,
		color->green,
		color->blue,
		color->alpha,
		color->red,
		color->green,
		color->blue,
		color->alpha,
	};

	GLfloat screen[] = {
		Framework::Get()->GetSize(1,1).x,
		Framework::Get()->GetSize(1,1).y,
		Framework::Get()->GetSize(1,1).x,
		Framework::Get()->GetSize(1,1).y,
		Framework::Get()->GetSize(1,1).x,
		Framework::Get()->GetSize(1,1).y,
		Framework::Get()->GetSize(1,1).x,
		Framework::Get()->GetSize(1,1).y,
	};
	GLfloat scale[] = {
		10.0f,10.0f,10.0f,10.0f
	};
	glAlphaFunc(GL_GREATER, (GLclampf)0.0);
	Shader* shader = texture->GetShader();
	shader->Use();
	GLint in_posLocation = shader->Attrib("inpos");
	GLint in_uvLocation = shader->Attrib("inuv");
	GLint in_texture = shader->Uniform("tex");
	GLuint in_color = shader->Attrib("incolor");
	GLuint in_proj = shader->Uniform("viewMatrix");

	GLuint in_screen = shader->Uniform("inscreen");
	GLuint in_scale = shader->Attrib("inscale");

	glEnableVertexAttribArray(in_posLocation);
	glEnableVertexAttribArray(in_uvLocation);
	glEnableVertexAttribArray(in_color);
	glEnableVertexAttribArray(in_scale);

	glUniform1f(in_texture, 0);
	glUniformMatrix4fv(in_proj, 1, GL_FALSE, Framework::Get()->GetScene()->GetCamera()->GetProjectionMatrix());
	glUniform2f(in_screen, screen[0], screen[1]);

	glVertexAttribPointer(in_posLocation, 2, GL_FLOAT, GL_FALSE, 0, vtx);
	glVertexAttribPointer(in_uvLocation, 2, GL_FLOAT, GL_FALSE, 0, texuv);
	glVertexAttribPointer(in_color, 4, GL_FLOAT, GL_FALSE, 0, texcolor);
	glVertexAttribPointer(in_scale, 1, GL_FLOAT, GL_FALSE, 0, scale);

	glBindTexture(GL_TEXTURE_2D, texture->GetID());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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