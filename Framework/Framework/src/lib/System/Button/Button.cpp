#include "Button.h"
#include "Input\Input.h"
#include "ResourceManager\ResourceManager.h"
Button::Button(const Transform& t)
{
	transform = t;
	tag = "Button";
	layer = Layer::Button;
	this->hitBase = new BoxCollider(&transform);
	this->back.texture = ResourceManager::Get()->GetTextureData("back");
	this->back.transform = &transform;
	this->back.color = &notSelect;
	this->font.transform = &transform;
	this->select = { 1,1,1,1 };
	this->notSelect = { 0.5f,0.5f,0.5f,1.0f };
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
	ChangeColor(Enable(Input::Get()->mouse->GetCollision()));
}