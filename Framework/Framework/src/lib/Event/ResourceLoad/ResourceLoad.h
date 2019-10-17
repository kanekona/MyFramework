#pragma once
#include <istream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/**
*@brief	���\�[�X��ǂݍ��ރC�x���gclass
*/
class CResourceLoad
{
	//!	�t�@�C���̒��g�̃f�[�^
	std::string textData;
	//! ��������f�[�^���
	std::string dataPath;
	//! �f�[�^�̃t�@�C����
	std::string dataName;
	/**
	*@brief	�f�[�^�𐶐�����
	*@param[in]	string text �������邽�߂̃f�[�^
	*/
	void DataCreate(const std::string& text);
public:
	/**
	*@brief	constructor
	*@param[in]	ifstream ifs �t�@�C���f�[�^
	*/
	explicit CResourceLoad(std::ifstream& ifs);
	/**
	*@brief	destructor
	*/
	virtual ~CResourceLoad();
};