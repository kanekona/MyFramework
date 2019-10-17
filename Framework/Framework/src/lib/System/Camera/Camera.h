#pragma once

#include "Collision\Collision.h"
#include "NonCopyable\NonCopyable.hpp"
#include "System\System.h"
/**
*@file Camera.h
*@brief Camera Class
*@author kanekona
*@data 2019/03/11
*@details 
*/

/**
*@brief Camera2D Class
*@details camera�s�������
*@details Scene�P�ɂPcamera�̐������s��
*/
class CCamera2D : private CNonCopyable
{
	//!	���ۈʒu
	CBox2D cameraPos;
	//!	�ʒu
	CVec2 position;
	//! �T�C�Y
	CVec2 scale;
	//! ���e�s���ۑ����Ă����z��
	GLfloat projectionMatrix[16];
	//! ����p
	CCircleCollider collision;
	//! Collider�l
	CTransform transform;
	/**
	*@brief	���e�s���o�^����
	*@param[in] float left ��
	*@param[in] float right �E
	*@param[in] float buttom ��
	*@param[in] float top ��
	*@param[in] float nearVal ��O
	*@param[in] float farVal ��
	*/
	void SetProjectionMatrix(
		const float left, const float right,
		const float buttom, const float top,
		const float nearVal, const float farVal);
public:
	/**
	*@brief	constructor
	*/
	explicit CCamera2D();
	/**
	*@brief	constructor
	*@param[in]	const Box2D& b �ʒu�ƃT�C�Y
	*/
	explicit CCamera2D(const CBox2D& b);
	/**
	*@brief	destructor
	*/
	virtual ~CCamera2D();
	/**
	*@brief	����������
	*@param[in]	const Box2D& b �ʒu�ƃT�C�Y
	*/
	void Initialize(const CBox2D& b);
	/**
	*@brief	�X�V����
	*/
	void Update();
	/**
	*@brief	�ʒu���ړ�������
	*@param[in] const Vec2& move �ړ��l
	*/
	void MovePos(const CVec2& move);
	/**
	*@brief	�ʒu��ݒ肷��
	*@param[in]	const Vec2& pos �ʒu
	*/
	void SetPos(const CVec2& pos);
	/**
	*@brief	�T�C�Y��ݒ肷��
	*@param[in]	const Vec2& size �傫��
	*/
	void SetSize(const CVec2& size);
	/**
	*@brief	�T�C�Y�𓮂���
	*@param[in]	const Vec2& move �ړ��l
	*/
	void MoveSize(const CVec2& move);
	/**
	*@brief	�J�����ʒu��X���W��ݒ肷��
	*@param[in]	float x ���W�l
	*/
	void SetPos_x(const float& x);
	/**
	*@brief	�J�����ʒu��Y���W��ݒ肷��
	*@param[in]	float y ���W�l
	*/
	void SetPos_y(const float& y);
	/**
	*@brief	�J�����̉��T�C�Y��ς���
	*@param[in]	float w ���T�C�Y
	*/
	void SetSize_w(const float& w);
	/**
	*@brief	�J�����̏c�T�C�Y��ς���
	*@param[in]	float w �c�T�C�Y
	*/
	void SetSize_h(const float& h);
	/**
	*@brief	�J�����̈ʒu��Ԃ�
	*@return Vec2 �J�����ʒu
	*/
	const CVec2& GetPos() const;
	/**
	*@brief	�J�����̃T�C�Y��Ԃ�
	*@return Vec2 �J�����̑傫��
	*/
	const CVec2& GetSize() const;
	/**
	*@brief	���e�s����擾����
	*@return GLfloat* ���e�s��
	*/
	const GLfloat* GetProjectionMatrix() const;
	/**
	*@brief Camera������擾
	*@return CollisionCircle* ����
	*/
	const CCircleCollider* GetCollision() const;
	/**
	*@brief �㉺���]�J�����s����擾����
	*@param[out] GLfloat* out ���e�s��
	*/
	void ReverseProjectionMatrix(GLfloat* out);
};