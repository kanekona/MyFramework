#pragma once
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS 
#include <stdio.h>
//common.h
#pragma warning (disable : 4244)
//corect_math_defines.h
#pragma warning (disable : 4005)
extern "C"
{
#include <libavutil\imgutils.h>
#include <libavcodec\avcodec.h>
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>
#include <libavfilter\avfilter.h>
}
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"avformat.lib")

#include "Sprite\Sprite.h"

/**
*FFmpeg‚ðŽg‚Á‚½“®‰æclass
*/

class MediaPlayer : Sprite
{
	AVFormatContext* format_context;
	void Update() override;
public:
	explicit MediaPlayer();
	virtual ~MediaPlayer();
	void Load(const std::string& path);
};