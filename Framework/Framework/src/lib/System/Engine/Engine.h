#pragma once
#include "Framerate\Framerate.h"
#define ERROR_GLFE_INIT 0x01
#define ERROR_GLEW_INIT 0x02

class CFramework;
class CWindow;
class CAudio;
class CInitializer;

/**
*@brief	Game Engine
*/
class CEngine : private CNonCopyable
{
	//! frame rate
	CFramerate fps;
	//! Main Framework
	CFramework* framework;
	//! MainFrame Window Address
	CWindow* window;
	//! Audiodevice
	CAudio* audiodevice;
	//! Engine Initializer
	CInitializer* initializer;
	//! Enable
	bool enable;
	/**
	*@brief	Outside Library Initializer
	*/
	void OutsideLibraryInitialize();
	/**
	*@brief	OpenGL OpenFW Initialize
	*/
	void GLFWInitialize();
public:
	/**
	*@brief	constructor
	*/
	explicit CEngine();
	/**
	*@brief	destructor
	*/
	virtual ~CEngine();
	/**
	*@brief	システム更新
	*@return bool System Continuation
	*/
	bool SystemUpdate();
};