#include "Button.h"
#include "Input\Input.h"
#include "ResourceManager\ResourceManager.h"
Button::Button(const Transform& t)
{
	transform = t;
	tag = "Button";
	layer = Layer::Button;
	this->hitBase = new BoxCollider(&transform);
	this->back.texture = ResourceManager::Get()->GetTextureData("button");
	this->back.transform = &transform;
	this->back.color = &notSelect;
	this->font.transform = &transform;
	notSelect = { 0.5f,0.5f,0.5f,1.0f };
	//Default
	SetDrawOrder(0);
}

Button::~Button()
{
	delete this->hitBase;
}

bool Button::Enable(Collider* collision)
{
	return this->hitBase->Hit(collision);
}

void Button::ChangeColor(const bool flag)
{
	if (flag)
	{
		this->back.color = &this->select;
	}
	else
	{
		this->back.color = &this->notSelect;
	}
}
void Button::Update()
{
	bool hit = Enable(Input::Get()->mouse->GetCollision());
	ChangeColor(hit);
	if (hit && Input::Get()->mouse->down(Mouse::LEFT))
	{
		this->Decision();
	}
}
void Button::Decision()
{

}

Font* Button::GetFont()
{
	return &this->font;
}

void Button::SetDrawOrder(const unsigned int o)
{
	this->order = o;
	font.SetDrawOrder(order + 1);
	back.SetDrawOrder(order);
}