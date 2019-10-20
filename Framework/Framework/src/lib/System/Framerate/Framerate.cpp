#include "Framerate.h"
CFramerate::CFramerate()
{
	Init(60);
}
CFramerate::CFramerate(const uint8 rate)
{
	Init(rate);
}
void CFramerate::Init(const uint8 rate)
{
	//�o�͗p�l
	fps = 0.f;
	//fps�v���p
#if DEBUG_ENABLE
	lastTime = (float)glfwGetTime();
	KL::DataClear("./data/debug/fpsrate.og");
#endif
	delta = 0.0f;
	SetFrameRate(rate);
}
void CFramerate::Update() 
{
#if DEBUG_ENABLE
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
CFramerate::~CFramerate()
{

}
void CFramerate::Reset()
{
	oneFrameTime = startDeltaTime = static_cast<float>(glfwGetTime());
	//oneFrameTime = static_cast<float>(glfwGetTime());
	frameCount = 1;
#if DEBUG_ENABLE
	count = 0;
#endif
}
void CFramerate::SetFrameRate(const uint8 rate)
{
	framerate = rate;
	Reset();
}
bool CFramerate::FrameCheck()
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
		if (frameCount == CMax::uInt64)
		{
			Reset();
		}
		return true;
	}
	return false;
}
float CFramerate::DeltaTime()
{
	return delta;
}