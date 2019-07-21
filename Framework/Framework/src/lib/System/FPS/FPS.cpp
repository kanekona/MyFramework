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
	fps = 0.f;
	//fps計測用
	lastTime = (float)glfwGetTime();
	KL::DataClear("./data/debug/fpsrate.og");
	delta = 0.0f;
	SetFrameRate(rate);
}
void FPS::Update() 
{
#ifdef KL_DEBUG
	//60回動作したらその時の時間と前の時間からfpsを求める
	if (count == framerate) {
		fps = count / ((float)glfwGetTime() - lastTime);
		std::cout << fps << std::endl;		//デバッグ時のみfpsを出力
	//	KL::OutDebugData("fpsrate.og", std::to_string(fps) + "\n");
		count = 0;
		lastTime = (float)glfwGetTime();
	}
	count++;
#endif
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
	framerate = rate;
	Reset();
}
bool FPS::FrameCheck()
{
	//( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) 何フレーム目かの計算
	//
	//if( ( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) == 0 )
	if ((float)glfwGetTime() - startDeltaTime >= (1.f / (float)framerate) * frameCount)
	{
		//oneFrameTime = (float)glfwGetTime();
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
	return delta;
}