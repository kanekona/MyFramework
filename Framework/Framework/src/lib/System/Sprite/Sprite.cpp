#include "Sprite.h"
#include "Engine\Framework.h"
#include "Engine\OGF.hpp"
Sprite::Sprite(const int registerd)
{
	this->Register(registerd);
}
Sprite::~Sprite()
{
}
void Sprite::Register(const int registerd)
{
	//SceneManager�o�R��RenderingManager�Ɏ�����o�^����
	switch (registerd)
	{
	case REGISTERD_CANVAS:
		Framework::Get()->GetScene()->GetRenderingManager()->AddSpriteCanvas(this);
		break;
	case REGISTERD_UI:
		Framework::Get()->GetScene()->GetRenderingManager()->AddSpriteUI(this);
		break;
	case REGISTERD_BACK:
		Framework::Get()->GetScene()->GetRenderingManager()->AddSpriteBack(this);
		break;
	default:
		//�G���[�o��
		std::cout << "�o�^�~�X\n";
		break;
	}
}
void Sprite::Draw()
{
	OGF::Draw(texture, transform, color);
}