#include "Button.h"
#include "Input\Input.h"
#include "ResourceManager\ResourceManager.h"
#include "Collision\Collision.h"
CButton::CButton(const CTransform& t)
	:back(true)
{
	transform = t;
	tag = "Button";
	layer = ELayer::Button;
	hitBase = new CBoxCollider(&transform);
	back.texture = CResourceManager::Get()->GetTextureData("button");
	back.transform = &transform;
	back.color = &notSelect;
	font.transform = &transform;
	notSelect = { 0.5f,0.5f,0.5f,1.0f };
	//Default
	SetDrawOrder(0);
}

CButton::~CButton()
{
	delete hitBase;
}

bool CButton::Enable(CCollider* collision)
{
	return hitBase->Hit(collision);
}

void CButton::ChangeColor(const bool flag)
{
	if (flag)
	{
		back.color = &select;
	}
	else
	{
		back.color = &notSelect;
	}
}
void CButton::Update()
{
	bool hit = Enable(CInput::Get()->mouse->GetCollision());
	ChangeColor(hit);
	if (hit && CInput::Get()->mouse->down(In::MOUSE_LEFT))
	{
		Decision();
	}
}
void CButton::Decision()
{

}

CFont* CButton::GetFont()
{
	return &font;
}

void CButton::SetDrawOrder(const unsigned int o)
{
	order = o;
	font.SetDrawOrder(order + 1);
	back.SetDrawOrder(order);
}