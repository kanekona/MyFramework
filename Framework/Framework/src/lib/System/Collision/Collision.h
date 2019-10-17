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
*@details �����蔻��class
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
	*@brief	�����蔻���Ԃ�
	*@param[in] CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	virtual bool Hit(CCollider* collision) = 0;
	//! Radius
	CVec2 radius;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) = 0;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider*b) = 0;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) = 0;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in]	CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) = 0;
	/**
	*@brief	���Ƃ̔���
	*@param[in]	CollisionLine* b ����̃I�u�W�F�N�g
	*@returnbool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) = 0;
};
/**
*@brief	��`����
*/
class CBoxCollider : public CCollider
{
	//! ��]�l
	float angle;
public:
	/**
	*@brief	constructor
	*/
	explicit CBoxCollider(CTransform* transform);
	//!	�����蔻��
	CBox2D hitBase;
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
	bool Hit(CCollider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���(������)
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	�~����
*/
class CCircleCollider : public CCollider
{
public:
	//! �����蔻��
	CCircle hitBase;
	/**
	*@brief	constructor
	*/
	explicit CCircleCollider(CTransform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	���Ƃ̔���(������)
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	�_����
*/
class CPointCollider : public CCollider
{
public:
	//! �����蔻��
	CVec2 hitBase;
	/**
	*@brief	constructor
	*/
	explicit CPointCollider(CTransform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���(������)
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	������
*/
class CLineCollider : public CCollider
{
public:
	//! �����蔻��
	CVec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CLineCollider(CTransform* transform);
	/**
	*@brief	�����蔻��𐶐�����
	*/
	void CreateCollision();
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};
/**
*@brief	�J�v�Z������
*! ������
*/
class CCapsuleCollider : public CCollider
{
public:
	//! �����蔻��
	CVec2 hitBase[2];
	/**
	*@brief	constructor
	*/
	explicit CCapsuleCollider(CTransform* transform);
	/**
	*@brief	�����蔻���Ԃ�
	*@param[in]	CollisionBase* collision ���葊��
	*@return bool true hit
	*/
	bool Hit(CCollider* collision) override;
	/**
	*@brief	��`�Ƃ̔���
	*@param[in] CollisionBox* b ����̃I�u�W�F�N�g
	*@return  bool �������Ă����true
	*/
	virtual bool GetHit(CBoxCollider* b) override;
	/**
	*@brief	�~�Ƃ̔���
	*@param[in] CollisionCircle* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCircleCollider* b) override;
	/**
	*@brief	�_�Ƃ̔���
	*@param[in] CollisionPointer* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CPointCollider* b) override;
	/**
	*@brief	���Ƃ̔���
	*@param[in] CollisionLine* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CLineCollider* b) override;
	/**
	*@brief	�J�v�Z���Ƃ̔���
	*@param[in] CollisionCapsule* b ����̃I�u�W�F�N�g
	*@return bool �������Ă����true
	*/
	virtual bool GetHit(CCapsuleCollider* b) override;
};