#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Window\Window.h"

class Scene;

/**
*@brief	初期化class
*初期化に必要な値を渡したりするclass
*/
class Initializer : private NonCopyable
{
public:
	/**
	*@brief	Windowの設定を渡す
	*@return WindowParameter Window Parameter
	*/
	WindowParameter ConfigWindow();
	/**
	*@brief	Begin Scene Adaptation
	*/
	Scene* SceneAdaptation();
};