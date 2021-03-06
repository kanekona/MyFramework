#pragma once
#include <istream>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

/**
*@brief	リソースを読み込むイベントclass
*/
class CResourceLoad
{
	//!	ファイルの中身のデータ
	std::string textData;
	//! 生成するデータ情報
	std::string dataPath;
	//! データのファイル名
	std::string dataName;
	/**
	*@brief	データを生成する
	*@param[in]	string text 生成するためのデータ
	*/
	void DataCreate(const std::string& text);
public:
	/**
	*@brief	constructor
	*@param[in]	ifstream ifs ファイルデータ
	*/
	explicit CResourceLoad(std::ifstream& ifs);
	/**
	*@brief	destructor
	*/
	virtual ~CResourceLoad();
};