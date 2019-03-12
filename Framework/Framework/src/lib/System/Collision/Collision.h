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
*@details �����蔻��class
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
	*@brief	�����蔻���Ԃ�
	*@param[in] CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	virtual bool Hit(Collider* collision) = 0;
	//! Radius
	Vec2 radius;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) = 0;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider*b) = 0;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) = 0;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in]	CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) = 0;
	/**
	*@brief	���Ƃ̔���
	*@param[in]	CollisionLine* b ����̃I�u�W�F�N�g
	*@returnbool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) = 0;
};
/**
*@brief	��`����
*/
class BoxCollider : public Collider
{
	//! ��]�l
	float angle;
public:
	/**
	*@brief	constructor
	*/
	explicit BoxCollider(Transform* transform);
	//!	�����蔻��
	Box2D hitBase;
	/**
	*@brief	��]�l��ύX����
	*@param[in] float _angle ��]�l
	*/
	void Rotate(const float _angle);
	/**
	*@brief	��]�l���擾����
	*@return float ��]�l
	*/
	float Rotate() const;
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���(������)
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	�~����
*/
class CircleCollider : public Collider
{
public:
	//! �����蔻��
	Circle hitBase;
	/**
	*@brief	constructor
	*/
	explicit CircleCollider(Transform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	���Ƃ̔���(������)
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	�_����
*/
class PointCollider : public Collider
{
public:
	//! �����蔻��
	Vec2 hitBase;
	/**
	*@brief	constructor
	*/
	explicit PointCollider(Transform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	������
*/
class LineCollider : public Collider
{
public:
	//! �����蔻��
	Vec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit LineCollider(Transform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};
/**
*@brief	�J�v�Z������
*! ������
*/
class CapsuleCollider : public Collider
{
public:
	//! �����蔻��
	Vec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CapsuleCollider(Transform* transform);
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(Collider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(BoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(PointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(LineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CapsuleCollider* b) override;
};