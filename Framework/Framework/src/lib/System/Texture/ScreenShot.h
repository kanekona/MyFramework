#pragma once
#include "Engine\Data.h"
#include "NonCopyable\NonCopyable.hpp"
#include "Engine\EngineTypedef.h"

enum class EScreenShotFormat : uint8
{
	//RGB = 3,
	RGBA = 4,
};

class CScreenShot : private CNonCopyable
{
public:
	static void Capture(const EScreenShotFormat InFormat = EScreenShotFormat::RGBA);

	static void Capture(const CBox2D& WinPos, const EScreenShotFormat InFormat = EScreenShotFormat::RGBA);
};