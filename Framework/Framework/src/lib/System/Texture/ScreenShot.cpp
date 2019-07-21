
#include "ScreenShot.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Engine\Framework.h"
#include "Window\Window.h"
#include <time.h>

void ScreenShot::Capture(const ScreenShotFormat InFormat)
{
	Capture(Box2D(Vec2Int(0, 0), Framework::Get()->GetWindow()->GetSize()), InFormat);
}

void ScreenShot::Capture(const Box2D & WinPos, const ScreenShotFormat InFormat)
{
	//GL_BACK,GL_FRONT
	glReadBuffer(GL_FRONT);
	const unsigned char format = (unsigned char)InFormat;
	unsigned char* data = new unsigned char[WinPos.w * WinPos.h * format];
	glReadPixels(WinPos.x, WinPos.y, WinPos.w, WinPos.h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//ècé≤Ç™ãtÇ…Ç»ÇÈÇÃÇ≈èCê≥
	for (int y = 0; y < WinPos.h / 2; ++y)
	{
		for (int x = 0; x < (int)WinPos.w; ++x)
		{
			unsigned char r = data[format * (y * (int)WinPos.w + x) + 0];
			unsigned char g = data[format * (y * (int)WinPos.w + x) + 1];
			unsigned char b = data[format * (y * (int)WinPos.w + x) + 2];
			unsigned char a = data[format * (y * (int)WinPos.w + x) + 3];

			data[format * (y * (int)WinPos.w + x) + 0] = data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 0];
			data[format * (y * (int)WinPos.w + x) + 1] = data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 1];
			data[format * (y * (int)WinPos.w + x) + 2] = data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 2];
			data[format * (y * (int)WinPos.w + x) + 3] = data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 3];

			data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 0] = r;
			data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 1] = g;
			data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 2] = b;
			data[format * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 3] = a;
		}
	}
	std::string filePath = "./data/image/ScreenShot/" + Framework::Get()->GetWindow()->GetTitle() + "_";
	time_t nowTime = time(NULL);
	tm TimeM;
	localtime_s(&TimeM, &nowTime);
	filePath += std::to_string(TimeM.tm_year + 1900);
	filePath += "_";
	filePath += std::to_string(TimeM.tm_mon + 1);
	filePath += "_";
	filePath += std::to_string(TimeM.tm_mday);
	filePath += "_";
	filePath += std::to_string(TimeM.tm_hour);
	filePath += "_";
	filePath += std::to_string(TimeM.tm_min);
	filePath += "_";
	filePath += std::to_string(TimeM.tm_sec);
	filePath += ".png";

	stbi_write_png(filePath.c_str(), WinPos.w, WinPos.h, format, data, 0);
	delete[] data;
}
