#include "Sprite.h"
#include "Engine\Framework.h"
#include "Texture\Texture.h"
#include "Engine\OGF.hpp"
#include "Engine\EngineMacro.h"
Sprite::Sprite(const bool flag,const int r)
	:registerd(r)
{
	if (flag)
	{
		Register();
	}
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
#if DEBUG_ENABLE
		std::cout << "�폜�~�X\n";
#endif
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
#if DEBUG_ENABLE
		std::cout << "�o�^�~�X\n";
#endif
		break;
	}
}
void Sprite::Draw()
{
	OGF::Draw(this, transform, color);
}
void Sprite::SetShaderData(Shader* shader)
{

}
void Sprite::SetDrawOrder(const unsigned int o)
{
	order = o;
}
void Sprite::CreateData()
{
	texture = new Texture();
	transform = new Transform();
	color = new Color();
}
void Sprite::DeleteData()
{
	delete texture;
	delete transform;
	delete color;
}
bool Sprite::Comparison(const Sprite* first, const Sprite* second)
{
	return first->order < second->order;
}