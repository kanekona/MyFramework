#pragma once
#include "Entity\Entity.h"
#include "Sprite\Sprite.h"
#include "Font\Font.h"
#include "Collision\Collision.h"
class Button : public Entity
{
	Collider* hitBase;
public:
	explicit Button(const Transform& transform);
	virtual ~Button();
	/**
	*@
	*‰Ÿ‚³‚ê‚Ä‚éó‹µ‚ğ•Ô‚·
	*‘Šè‚Ì”»’è‚ğ‚¢‚ê‚Ä‚»‚Ì”»’è‚ğ•Ô‚·
	*/
	bool Enable(Collider* collision);
	void ChangeColor(const bool flag);
	virtual void Update() override;
protected:
	Color select;
	Color notSelect;
	Font font;
	Sprite back;
	Transform transform;
};