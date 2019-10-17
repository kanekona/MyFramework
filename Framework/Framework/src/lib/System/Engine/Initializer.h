#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Window\Window.h"

class CScene;

/**
*@brief	‰Šú‰»class
*‰Šú‰»‚É•K—v‚È’l‚ğ“n‚µ‚½‚è‚·‚éclass
*/
class CInitializer : private CNonCopyable
{
public:
	/**
	*@brief	Window‚Ìİ’è‚ğ“n‚·
	*@return WindowParameter Window Parameter
	*/
	CWindowParameter ConfigWindow();
	/**
	*@brief	Begin Scene Adaptation
	*/
	CScene* SceneAdaptation();
};