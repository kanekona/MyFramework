#pragma once
#include "Engine\Data.h"
#include "NonCopyable\NonCopyable.hpp"

enum class ScreenShotFormat : unsigned char
{
	RGB = 3,
	RGBA = 4,
};

class ScreenShot : private NonCopyable
{
public:
	static void Capture(const ScreenShotFormat InFormat = ScreenShotFormat::RGBA);

	static void Capture(const Box2D& WinPos, const ScreenShotFormat InFormat);
};