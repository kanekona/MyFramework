
#pragma once
#include "System\System.h"
#include "NonCopyable\NonCopyable.hpp"
/**
*@brief	�����Ԃ𓱂����߂�class
*/
class CTime : private CNonCopyable
{
	//! �����^�C��
	float initTime;
	//! ���݃^�C��
	float nowTime;
	//! ��~���̃^�C���̕ۑ�
	float saveTime;
	//! �ǉ��^�C��
	float addTime;
	//! �v��������
	bool isPlay;
	//! ���쒆����
	bool behavior;
	/**
	*@brief ������
	*/
	void Init();
	/**
	*@brief ���l�̏�����
	*/
	void InitNumber();
public:
	/**
	*@brief	constructor
	*/
	explicit CTime();
	/**
	*@brief	destructor
	*/
	virtual ~CTime();
	/**
	*@brief	�v���J�n
	*/
	void Start();
	/**
	*@brief	�v����~
	*/
	void Stop();
	/**
	*@brief	�ꎞ��~
	*@param[in] bool isPlay Time Pause
	*/
	void Pause(const bool isPause);
	/**
	*@brief	���݃^�C����Ԃ�
	*@return float ���݂̃^�C��
	*/
	float GetTime();
	/**
	*@brief	�J�n�^�C���̕ύX
	*@param[in] float time_ �������̃^�C��
	*/
	void InitTime(const float time_);
	/**
	*@brief	�v������
	*@return bool �v�����s���Ă��邩���ׂ�
	*/
	bool IsPlay() const;
	/**
	*@brief �^�C���̃��Z�b�g
	*/
	void Reset(const float time = 0.0f);
};