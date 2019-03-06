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
		std::cout << "登録ミス\n";
		break;
	}
}
void Sprite::Draw()
{
	OGF::Draw(texture, transform, color);
}