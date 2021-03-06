#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Window\Window.h"

class CScene;

/**
*@brief	初期化class
*初期化に必要な値を渡したりするclass
*/
class CInitializer : private CNonCopyable
{
public:
	/**
	*@brief	Windowの設定を渡す
	*@return WindowParameter Window Parameter
	*/
	CWindowParameter ConfigWindow();
	/**
	*@brief	Begin Scene Adaptation
	*/
	CScene* SceneAdaptation();
};