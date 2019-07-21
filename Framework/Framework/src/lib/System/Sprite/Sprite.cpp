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
	//登録解除
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
		//エラー出力
#if DEBUG_ENABLE
		std::cout << "削除ミス\n";
#endif
		break;
	}
}
void Sprite::Register()
{
	//SceneManager経由でRenderingManagerに自分を登録する
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
		//エラー出力
#if DEBUG_ENABLE
		std::cout << "登録ミス\n";
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