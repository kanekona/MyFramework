
#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Engine\EngineTypedef.h"
#include "System\System.h"
/**
*@brief	フレームレートを計算,制限するclass
*
*既存GameEngineを使用している場合はUpdateをDEBUG時のみ行う
*/
class CFramerate : private CNonCopyable 
{
#if DEBUG_ENABLE
	//! 全フレームタイム
	float lastTime;
	//! カウント数
	uint32 count;
#endif
	//! fps値
	GLfloat fps;
	//! frame rate
	uint8 framerate;
	//! oneframetime
	float oneFrameTime;
	//! FrameCount
	uint64 frameCount;
	//! StartDeltaTime
	float startDeltaTime;
	//! DeltaTime
	float delta;
	/**
	*@brief Reset Data
	*/
	void Reset();
	/**
	*@brief Initialize
	*@param[in] float rate Framerate
	*/
	void Init(const uint8 rate);
public:
	/**
	*@brief	constructor
	*/
	explicit CFramerate();			
	/**
	*@brief constructor
	*@param[in] float rate Framerate
	*/
	explicit CFramerate(const uint8 rate);
	/**
	*@brief	destructor
	*/
	virtual ~CFramerate();
	/**
	*@brief	更新処理
	*/
	void Update();
	/**
	*@bried	フレームレート指定
	*@param[in]	int rate frame rate
	*/
	void SetFrameRate(const uint8 rate);
	/**
	*@brief	フレームチェック
	*@return 秒間フレームに達しているならtrue
	*/
	bool FrameCheck();
	/**
	*@brief Get DeltaTime
	*@return float DeltaTime
	*/
	float DeltaTime();
};
