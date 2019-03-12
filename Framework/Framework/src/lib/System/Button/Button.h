#pragma once
#include "Entity\Entity.h"
#include "Sprite\Sprite.h"
#include "Font\Font.h"
#include "Collision\Collision.h"
/**
*@file Button.h
*@brief Button Class
*@author kanekona
*@data 2019/03/11
*@details
*/

/**
*@brief Button Class
*@details Click Action
*/
class Button : public Entity
{
	//! Button Collision
	Collider* hitBase;
	//! Draw Order
	unsigned int order;
public:
	/**
	*@brief	constructor
	*@param[in] Transform& transform Button Transform
	*/
	explicit Button(const Transform& transform);
	/**
	*@brief	destructor
	*/
	virtual ~Button();
	/**
	*@brief This Hit Check
	*@param[in] Collider* collision Partner Collider
	*@return bool Hit
	*@details �����Ƃ̔�����s�����̌��ʂ�Ԃ�
	*/
	bool Enable(Collider* collision);
	/**
	*@brief This Color Chenge
	*@param[in] bool flag Color Branch
	*@details �����ɉ����đI������I���̃J���[�ɕύX����
	*/
	void ChangeColor(const bool flag);
	/**
	*@brief	Set Button Draw Order
	*@param[in] unsigned int order Order
	*/
	void SetDrawOrder(const unsigned int order);
	/**
	*@brief This Update
	*@details Button�̍X�V����
	*/
	virtual void Update() override;
	/**
	*@brief	Default Decision
	*@details ���莞�̏�����Default����
	*�p����ł��̊֐���override���Č��菈����ύX����
	*/
	virtual void Decision();
	/**
	*@brief	Get Button Font
	*@return Font* This FontData
	*@details Button����Font�f�[�^���擾����
	*/
	Font* GetFont();
protected:
	//! Select Color
	Color select;
	//! Not Select Color
	Color notSelect;
	//! Font
	Font font;
	//! Back Image
	Sprite back;
	//! Transform
	Transform transform;
};