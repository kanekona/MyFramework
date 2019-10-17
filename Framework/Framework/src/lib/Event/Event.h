#pragma once
#include <fstream>
#include "Engine\EngineTypedef.h"
/**
*enum class Event
*@brief	�ǂݍ��ރC�x���g�̎��
*/
enum class EEvent : uint8
{
	//! ���\�[�X�ǂݍ��݃C�x���g
	RESOURCE_LOAD,
	WINDOW_CHANGE,
	INPUT_CONFIG
};

/**
*@brief	�C�x���g�^�X�N
*/
class CEventTask
{
	//! �t�@�C�����
	std::ifstream ifs;
public:
	/**
	*@brief	constructor
	*/
	explicit CEventTask();
	/**
	*@brief	destructor
	*/
	virtual ~CEventTask();
	/**
	*@brief	�C�x���g��ǂݍ���
	*@param[in]	Event eventType ��������Event�̎��
	*@param[in]	string path �ǂݍ���Event�t�@�C���̃p�X
	*@return	bool ����true
	*/
	bool Load(const EEvent& eventType, const std::string& path);
};