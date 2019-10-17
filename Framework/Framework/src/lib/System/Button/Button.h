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
	*@details 引数との判定を行いその結果を返す
	*/
	bool Enable(CCollider* collision);
	/**
	*@brief This Color Chenge
	*@param[in] bool flag Color Branch
	*@details 引数に応じて選択か非選択のカラーに変更する
	*/
	void ChangeColor(const bool flag);
	/**
	*@brief	Set Button Draw Order
	*@param[in] unsigned int order Order
	*/
	void SetDrawOrder(const unsigned int order);
	/**
	*@brief This Update
	*@details Buttonの更新処理
	*/
	virtual void Update() override;
	/**
	*@brief	Default Decision
	*@details 決定時の処理のDefault処理
	*継承先でこの関数をoverrideして決定処理を変更する
	*/
	virtual void Decision();
	/**
	*@brief	Get Button Font
	*@return Font* This FontData
	*@details Button内のFontデータを取得する
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