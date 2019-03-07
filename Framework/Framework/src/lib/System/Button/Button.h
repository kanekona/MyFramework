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
	*押されてる状況を返す
	*相手の判定をいれてその判定を返す
	*/
	bool Enable(Collider* collision);
	void ChangeColor(const bool flag);
	virtual void Update() override;
	virtual void Decision();
protected:
	Color select;
	Color notSelect;
	Font font;
	Sprite back;
	Transform transform;
};