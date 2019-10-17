
#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Engine\EngineTypedef.h"
#include "System\System.h"
/**
*@brief	�t���[�����[�g���v�Z,��������class
*
*����GameEngine���g�p���Ă���ꍇ��Update��DEBUG���̂ݍs��
*/
class CFramerate : private CNonCopyable 
{
#if DEBUG_ENABLE
	//! �S�t���[���^�C��
	float lastTime;
	//! �J�E���g��
	uint32 count;
#endif
	//! fps�l
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
	*@brief	�X�V����
	*/
	void Update();
	/**
	*@bried	�t���[�����[�g�w��
	*@param[in]	int rate frame rate
	*/
	void SetFrameRate(const uint8 rate);
	/**
	*@brief	�t���[���`�F�b�N
	*@return �b�ԃt���[���ɒB���Ă���Ȃ�true
	*/
	bool FrameCheck();
	/**
	*@brief Get DeltaTime
	*@return float DeltaTime
	*/
	float DeltaTime();
};
