#include "FPS.h"
FPS::FPS()
{
	Init(60.0f);
}
FPS::FPS(const float rate)
{
	Init(rate);
}
void FPS::Init(const float rate)
{
	//出力用値
	this->fps = 0.f;
	//fps計測用
	this->lastTime = (float)glfwGetTime();
	KL::DataClear("./data/debug/fpsrate.og");
	delta = 0.0f;
	SetFrameRate(rate);
}
void FPS::Update() 
{
	//60回動作したらその時の時間と前の時間からfpsを求める
	if (this->count == this->framerate) {
		this->fps = this->count / ((float)glfwGetTime() - this->lastTime);
		std::cout << this->fps << std::endl;		//デバッグ時のみfpsを出力
	//	KL::OutDebugData("fpsrate.og", std::to_string(this->fps) + "\n");
		this->count = 0;
		this->lastTime = (float)glfwGetTime();
	}
	this->count++;
}
FPS::~FPS()
{

}
void FPS::Reset()
{
	startDeltaTime = static_cast<float>(glfwGetTime());
	oneFrameTime = static_cast<float>(glfwGetTime());
	frameCount = 1;
	count = 0;
}
void FPS::SetFrameRate(const int rate)
{
	this->framerate = rate;
	Reset();
}
bool FPS::FrameCheck()
{
	//( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) 何フレーム目かの計算
	//
	//if( ( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) == 0 )
	if ((float)glfwGetTime() - this->startDeltaTime >= (1.f / (float)this->framerate) * this->frameCount)
	{
		//this->oneFrameTime = (float)glfwGetTime();
		//デルタタイムを計算する処理
		delta = (float)glfwGetTime() - oneFrameTime;
		oneFrameTime = (float)glfwGetTime();

		++frameCount;
		return true;
	}
	return false;
}
float FPS::DeltaTime()
{
	return this->delta;
}