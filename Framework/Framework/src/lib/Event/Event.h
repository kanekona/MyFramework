#pragma once
#include <fstream>
#include "Engine\EngineTypedef.h"
/**
*enum class Event
*@brief	読み込むイベントの種類
*/
enum class EEvent : uint8
{
	//! リソース読み込みイベント
	RESOURCE_LOAD,
	WINDOW_CHANGE,
	INPUT_CONFIG
};

/**
*@brief	イベントタスク
*/
class CEventTask
{
	//! ファイル情報
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
	*@brief	イベントを読み込む
	*@param[in]	Event eventType 生成するEventの種類
	*@param[in]	string path 読み込むEventファイルのパス
	*@return	bool 成功true
	*/
	bool Load(const EEvent& eventType, const std::string& path);
};