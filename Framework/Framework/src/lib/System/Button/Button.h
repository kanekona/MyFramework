#pragma once
#include "Entity\Entity.h"
#include "Sprite\Sprite.h"
#include "Font\Font.h"
/**
*@file Button.h
*@brief Button Class
*@author kanekona
*@data 2019/03/11
*@details
*/

class CCollider;

/**
*@brief Button Class
*@details Click Action
*/
class CButton : public CEntity
{
	//! Button Collision
	CCollider* hitBase;
	//! Draw Order
	unsigned int order;
public:
	/**
	*@brief	constructor
	*@param[in] Transform& transform Button Transform
	*/
	explicit CButton(const CTransform& transform);
	/**
	*@brief	destructor
	*/
	virtual ~CButton();
	/**
	*@brief This Hit Check
	*@param[in] Collider* collision Partner Collider
	*@return bool Hit
	*@details �����Ƃ̔�����s�����̌��ʂ�Ԃ�
	*/
	bool Enable(CCollider* collision);
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
	CFont* GetFont();
protected:
	//! Select Color
	CColor select;
	//! Not Select Color
	CColor notSelect;
	//! Font
	CFont font;
	//! Back Image
	CSprite back;
	//! Transform
	CTransform transform;
};