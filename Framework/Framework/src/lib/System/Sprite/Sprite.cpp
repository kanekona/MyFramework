#include "Sprite.h"
#include "Engine\Framework.h"
#include "Engine\OGF.hpp"
Sprite::Sprite(const int r)
	:registerd(r)
{
	this->Register();
}
Sprite::~Sprite()
{
	//�o�^����
	switch (registerd)
	{
	case REGISTERD_CANVAS:
		Framework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteCanvas(this);
		break;
	case REGISTERD_UI:
		Framework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteUI(this);
		break;
	case REGISTERD_BACK:
		Framework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteBack(this);
		break;
	default:
		//�G���[�o��
		std::cout << "�폜�~�X\n";
		break;
	}
}
void Sprite::Register()
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
void Sprite::SetDrawOrder(const unsigned int o)
{
	order = o;
}
bool Sprite::Comparison(const Sprite* first, const Sprite* second)
{
	return first->order < second->order;
}