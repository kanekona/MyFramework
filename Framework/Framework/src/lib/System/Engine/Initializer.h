#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Window\Window.h"

class CScene;

/**
*@brief	������class
*�������ɕK�v�Ȓl��n�����肷��class
*/
class CInitializer : private CNonCopyable
{
public:
	/**
	*@brief	Window�̐ݒ��n��
	*@return WindowParameter Window Parameter
	*/
	CWindowParameter ConfigWindow();
	/**
	*@brief	Begin Scene Adaptation
	*/
	CScene* SceneAdaptation();
};