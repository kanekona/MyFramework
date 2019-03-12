#pragma once
#include "System\System.h"
#include "Engine\Data.h"
class Collider;
class BoxCollider;
class CircleCollider;
class PointCollider;
class LineCollider;
class CapsuleCollider;

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
class Collider
{
protected:
	//! Vertex Number
	const unsigned short VERTEX_NUM;
	//! Transform
	Transform* transform;
public:
	/**
	*@brief	constructor
	*@param[in]	unsigned short vertex VertexNumber
	*/
	explicit Collider(const unsigned short vertex,Transform* transform);
	/**
	*@brief	当たり判定を返す
	*@param[in] CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	virtual bool Hit(Collider* collision) = 0;
	//! Radius
	Vec2 radius;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) = 0;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider*b) = 0;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) = 0;
	/**
	*@brief	カプセルとの判定
	*@param[in]	CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) = 0;
	/**
	*@brief	線との判定
	*@param[in]	CollisionLine* b 相手のオブジェクト
	*@returnbool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) = 0;
};
/**
*@brief	矩形判定
*/
class BoxCollider : public Collider
{
	//! 回転値
	float angle;
public:
	/**
	*@brief	constructor
	*/
	explicit BoxCollider(Transform* transform);
	//!	当たり判定
	Box2D hitBase;
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
	bool Hit(Collider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	点との判定(未完成)
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	円判定
*/
class CircleCollider : public Collider
{
public:
	//! 当たり判定
	Circle hitBase;
	/**
	*@brief	constructor
	*/
	explicit CircleCollider(Transform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	線との判定(未完成)
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	点判定
*/
class PointCollider : public Collider
{
public:
	//! 当たり判定
	Vec2 hitBase;
	/**
	*@brief	constructor
	*/
	explicit PointCollider(Transform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	カプセルとの判定(未完成)
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	線判定
*/
class LineCollider : public Collider
{
public:
	//! 当たり判定
	Vec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit LineCollider(Transform* transform);
	/**
	*@brief	当たり判定を生成する
	*/
	void CreateCollision();
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	カプセルとの判定
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	カプセル判定
*! 未完成
*/
class CapsuleCollider : public Collider
{
public:
	//! 当たり判定
	Vec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CapsuleCollider(Transform* transform);
	/**
	*@brief	当たり判定を返す
	*@param[in]	CollisionBase* collision 判定相手
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	矩形との判定
	*@param[in] CollisionBox* b 相手のオブジェクト
	*@return  bool 当たっていればtrue
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	円との判定
	*@param[in] CollisionCircle* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	点との判定
	*@param[in] CollisionPointer* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	線との判定
	*@param[in] CollisionLine* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	カプセルとの判定
	*@param[in] CollisionCapsule* b 相手のオブジェクト
	*@return bool 当たっていればtrue
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};