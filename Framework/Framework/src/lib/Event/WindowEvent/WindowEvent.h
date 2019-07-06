#pragma once
#include <fstream>
#include <sstream>
class WindowEvent
{
public:
	/**
	*@brief	constructor
	*@param[in] ifstream& ifs ファイルデータ
	*@param[out] int* x X値
	*@param[out] int* y Y値
	*/
	explicit WindowEvent(std::ifstream& ifs, int* x, int* y);
	/**
	*@brief	constructor
	*@param[in] ifstream& ifs ファイルデータ
	*@param[out] WindowParameter* parameter
	*/
	explicit WindowEvent(std::ifstream& ifs);

	/**
	*@brief	destructor
	*/
	virtual ~WindowEvent();
};