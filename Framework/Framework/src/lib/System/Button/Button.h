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
	*������Ă�󋵂�Ԃ�
	*����̔��������Ă��̔����Ԃ�
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