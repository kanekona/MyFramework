#pragma once
#include <fstream>
#include <sstream>
#include "Window\Window.h"
class WindowEvent
{
public:
	/**
	*@brief	constructor
	*@param[in] ifstream& ifs �t�@�C���f�[�^
	*@param[out] int* x X�l
	*@param[out] int* y Y�l
	*/
	explicit WindowEvent(std::ifstream& ifs, int* x, int* y);
	/**
	*@brief	constructor
	*@param[in] ifstream& ifs �t�@�C���f�[�^
	*@param[out] WindowParameter* parameter
	*/
	//explicit WindowEvent(std::ifstream& ifs, WindowParameter* parameter);

	/**
	*@brief	destructor
	*/
	virtual ~WindowEvent();
};