#include "Button.h"
#include "Input\Input.h"
#include "ResourceManager\ResourceManager.h"
#include "Collision\Collision.h"
Button::Button(const Transform& t)
	:back(true)
{
	transform = t;
	tag = "Button";
	layer = Layer::Button;
	hitBase = new BoxCollider(&transform);
	back.texture = ResourceManager::Get()->GetTextureData("button");
	back.transform = &transform;
	back.color = &notSelect;
	font.transform = &transform;
	notSelect = { 0.5f,0.5f,0.5f,1.0f };
	//Default
	SetDrawOrder(0);
}

Button::~Button()
{
	delete hitBase;
}

bool Button::Enable(Collider* collision)
{
	return hitBase->Hit(collision);
}

void Button::ChangeColor(const bool flag)
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
void Button::Update()
{
	bool hit = Enable(Input::Get()->mouse->GetCollision());
	ChangeColor(hit);
	if (hit && Input::Get()->mouse->down(Mouse::LEFT))
	{
		Decision();
	}
}
void Button::Decision()
{

}

Font* Button::GetFont()
{
	return &font;
}

void Button::SetDrawOrder(const unsigned int o)
{
	order = o;
	font.SetDrawOrder(order + 1);
	back.SetDrawOrder(order);
}