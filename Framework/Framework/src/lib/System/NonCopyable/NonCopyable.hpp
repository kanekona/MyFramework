#pragma once
/**
*@brief	�R�s�[���֎~����class
*
*����class���p������class�̓R�s�[�R���X�g���N�^�Ƒ�����Z���֎~����܂�
*/
class CNonCopyable
{
	void operator=(const CNonCopyable&) = delete;
	CNonCopyable(const CNonCopyable&) = delete;
protected:
	explicit CNonCopyable()
	{

	}
	virtual ~CNonCopyable()
	{

	}
};