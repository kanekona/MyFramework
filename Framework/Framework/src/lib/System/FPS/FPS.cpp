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
	//�o�͗p�l
	fps = 0.f;
	//fps�v���p
	lastTime = (float)glfwGetTime();
	KL::DataClear("./data/debug/fpsrate.og");
	delta = 0.0f;
	SetFrameRate(rate);
}
void FPS::Update() 
{
#ifdef KL_DEBUG
	//60�񓮍삵���炻�̎��̎��ԂƑO�̎��Ԃ���fps�����߂�
	if (count == framerate) {
		fps = count / ((float)glfwGetTime() - lastTime);
		std::cout << fps << std::endl;		//�f�o�b�O���̂�fps���o��
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
	//( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) ���t���[���ڂ��̌v�Z
	//
	//if( ( (float)glfwGetTime() - startTime ) / (1.f / (float)framerate) == 0 )
	if ((float)glfwGetTime() - startDeltaTime >= (1.f / (float)framerate) * frameCount)
	{
		//oneFrameTime = (float)glfwGetTime();
		//�f���^�^�C�����v�Z���鏈��
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