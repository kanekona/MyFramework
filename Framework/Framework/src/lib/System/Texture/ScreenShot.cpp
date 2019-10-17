
#include "ScreenShot.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Engine\Framework.h"
#include "Window\Window.h"
#include <time.h>

void CScreenShot::Capture(const EScreenShotFormat InFormat)
{
	Capture(CBox2D(CVec2Int(0, 0), CFramework::Get()->GetWindow()->GetSize()), InFormat);
}

void CScreenShot::Capture(const CBox2D & WinPos, const EScreenShotFormat InFormat)
{
	//GL_BACK,GL_FRONT
	glReadBuffer(GL_FRONT);
	const unsigned char TFormat = (unsigned char)InFormat;
	unsigned char* data = new unsigned char[WinPos.w * WinPos.h * TFormat];
	glReadPixels(WinPos.x, WinPos.y, WinPos.w, WinPos.h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//ècé≤Ç™ãtÇ…Ç»ÇÈÇÃÇ≈èCê≥
	for (int y = 0; y < WinPos.h / 2; ++y)
	{
		for (int x = 0; x < (int)WinPos.w; ++x)
		{
			unsigned char r = data[TFormat * (y * (int)WinPos.w + x) + 0];
			unsigned char g = data[TFormat * (y * (int)WinPos.w + x) + 1];
			unsigned char b = data[TFormat * (y * (int)WinPos.w + x) + 2];
			unsigned char a = data[TFormat * (y * (int)WinPos.w + x) + 3];

			data[TFormat * (y * (int)WinPos.w + x) + 0] = data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 0];
			data[TFormat * (y * (int)WinPos.w + x) + 1] = data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 1];
			data[TFormat * (y * (int)WinPos.w + x) + 2] = data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 2];
			data[TFormat * (y * (int)WinPos.w + x) + 3] = data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 3];

			data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 0] = r;
			data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 1] = g;
			data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 2] = b;
			data[TFormat * (((int)WinPos.h - 1 - y) * (int)WinPos.w + x) + 3] = a;
		}
	}
	std::string filePath = "./data/image/ScreenShot/" + CFramework::Get()->GetWindow()->GetTitle() + "_";
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

	stbi_write_png(filePath.c_str(), WinPos.w, WinPos.h, TFormat, data, 0);
	delete[] data;
}
