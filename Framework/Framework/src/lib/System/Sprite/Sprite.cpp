#include "Sprite.h"
#include "Engine\Framework.h"
#include "Texture\Texture.h"
#include "Engine\OGF.hpp"
#include "Engine\EngineMacro.h"
CSprite::CSprite(const bool flag,const int r)
	:registerd(r)
{
	if (flag)
	{
		Register();
	}
	IsDeleteData = false;
}
CSprite::~CSprite()
{
	//登録解除
	Release();
	if (IsDeleteData)
	{
		DeleteData();
	}
}
void CSprite::Register()
{
	//SceneManager経由でRenderingManagerに自分を登録する
	switch (registerd)
	{
	case REGISTERD_CANVAS:
		CFramework::Get()->GetScene()->GetRenderingManager()->AddSpriteCanvas(this);
		break;
	case REGISTERD_UI:
		CFramework::Get()->GetScene()->GetRenderingManager()->AddSpriteUI(this);
		break;
	case REGISTERD_BACK:
		CFramework::Get()->GetScene()->GetRenderingManager()->AddSpriteBack(this);
		break;
	default:
		//エラー出力
#if DEBUG_ENABLE
		std::cout << "登録ミス\n";
#endif
		break;
	}
}
void CSprite::Release()
{
	switch (registerd)
	{
	case REGISTERD_CANVAS:
		CFramework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteCanvas(this);
		break;
	case REGISTERD_UI:
		CFramework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteUI(this);
		break;
	case REGISTERD_BACK:
		CFramework::Get()->GetScene()->GetRenderingManager()->DeleteSpriteBack(this);
		break;
	default:
		//エラー出力
#if DEBUG_ENABLE
		std::cout << "削除ミス\n";
#endif
		break;
	}
}
void CSprite::Draw()
{
	COGF::Draw(this, transform, color);
}
void CSprite::SetShaderData(CShader* shader)
{

}
void CSprite::SetDrawOrder(const unsigned int o)
{
	order = o;
}
void CSprite::CreateData()
{
	texture = new CTexture();
	transform = new CTransform();
	color = new CColor();
	IsDeleteData = true;
}
void CSprite::DeleteData()
{
	delete texture;
	delete transform;
	delete color;
	IsDeleteData = false;
}
bool CSprite::Comparison(const CSprite* first, const CSprite* second)
{
	return first->order < second->order;
}