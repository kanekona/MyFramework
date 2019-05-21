#pragma once
#include "Sprite\Sprite.h"

typedef std::string format;
/**
*@brief	MovieImage Format
*/
class MovieFormat
{
public:
	//! MP3
	const static format MP3;
	//! MP3
	const static format MP4;
	//! AVI
	const static format AVI;
	//! WAV
	const static format WAV;
};

class MovieImage : public Sprite
{
	//! OpenCV行列
	cv::Mat	mat;
	//! キャプチャを行う
	cv::VideoCapture videoCapture;
	//!　読み込んだ動画のフレームレート
	float videoFramerate;
	//! 動画の再生速度の倍率
	float magnification;
	//! 動画のループ設定
	bool loop;
	//! 再生状態
	bool enablePlay;
	//! 再生の前状態
	bool preEnablePlay;
	/**
	*@brief OpenCV Open
	*/
	void CV_Open(const std::string& path);
public:
	/**
	*@brief constructor
	*/
	explicit MovieImage();
	/**
	*@brief destructor
	*/
	virtual ~MovieImage();
protected:
};