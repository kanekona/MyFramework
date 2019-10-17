#pragma once
#include "System\System.h"

class CCollider;
class CBoxCollider;
class CCircleCollider;
class CPointCollider;
class CLineCollider;
class CCapsuleCollider;

/**
*@file Collision.h
*@brief Collider System
*@author kanekona
*@data 2019/03/11
*@details 当たり判定class
*/

/**
*@brief Collider Class
*@details Collider Base
*/
class CCollider
{
protected:
	//! Vertex Number
	const unsigned short VERTEX_NUM;
	//! Transform
	CTransform* transform;
public:
	/**
	*@brief	constructor
	*@param[in]	unsigned short vertex VertexNumber
	*/
	explicit CCollider(const unsigned short vertex,CTransform* transform);
	/**
	*@brief	当たり判定を返す
	*@param[in] CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	virtual bool Hit(CCollider* collision) = 0;
	//! Radius
	CVec2 radius;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) = 0;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider*b) = 0;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) = 0;
	/**
	*@brief	カプセルとの判定
	*@param[in]	CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) = 0;
	/**
	*@brief	線との判定
	*@param[in]	CollisionLine* b 相手のオブジェクト
	*@returnbool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) = 0;
};
/**
*@brief	矩形判定
*/
class CBoxCollider : public CCollider
{
	//! 回転値
	float angle;
public:
	/**
	*@brief	constructor
	*/
	explicit CBoxCollider(CTransform* transform);
	//!	当たり判定
	CBox2D hitBase;
	/**
	*@brief	回転値を変更する
	*@param[in] float _angle 回転値
	*/
	void Rotate(const float _angle);
	/**
	*@brief	回転値を取得する
	*@return float 回転値
	*/
	float Rotate() const;
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	点との判定(未完成)
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	円判定
*/
class CCircleCollider : public CCollider
{
public:
	//! 当たり判定
	CCircle hitBase;
	/**
	*@brief	constructor
	*/
	explicit CCircleCollider(CTransform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	線との判定(未完成)
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	点判定
*/
class CPointCollider : public CCollider
{
public:
	//! 当たり判定
	CVec2 hitBase;
	/**
	*@brief	constructor
	*/
	explicit CPointCollider(CTransform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	線判定
*/
class CLineCollider : public CCollider
{
public:
	//! 当たり判定
	CVec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CLineCollider(CTransform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	カプセルとの判定
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	カプセル判定
*! 未完成
*/
class CCapsuleCollider : public CCollider
{
public:
	//! 当たり判定
	CVec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CCapsuleCollider(CTransform* transform);
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	カプセルとの判定
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};