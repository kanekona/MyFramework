#pragma once
#include "Sprite\Sprite.h"
#include "System\System.h"

typedef std::string TFormat;
/**
*@brief	MovieImage Format
*/
class CMovieFormat
{
public:
	//! MP3
	const static TFormat MP3;
	//! MP3
	const static TFormat MP4;
	//! AVI
	const static TFormat AVI;
	//! WAV
	const static TFormat WAV;
};

class CMovieImage : public CSprite
{
protected:
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
	/**
	*@brief OpenCV Video Set Frame
	*@param[in] float frame Video Frame
	*/
	void CV_SetFrame(const float frame);
	/**
	*@brief Set OpenCV Mat to Texture
	*@return bool Mat Empty
	*/
	bool SetMatToTexture();
	/**
	*@brief Initializer
	*/
	virtual void Init();
	/**
	*@brief Delete This Class
	*/
	virtual void Delete();
	/**
	*@brief Play Video
	*/
	virtual void Play();
	/**
	*@brief Pause Video
	*/
	virtual void Pause();
public:
	/**
	*@brief constructor
	*/
	explicit CMovieImage();
	/**
	*@brief destructor
	*/
	virtual ~CMovieImage();
	/**
	*@brief Set Play Video
	*@param[in] bool isPlay enable video play
	*/
	virtual void SetPlay(const bool isPlay);
	/**
	*@brief Set Speed
	*@param[in] float speed Video Speed
	*/
	virtual void SetSpeed(const float speed);
	/**
	*@brief Set Video Time
	*@param[in] float time Video Time
	*/
	virtual void SetTime(const float time);
	/**
	*@brief Set Lopping
	*@param[in] bool isLoop Video Looping
	*/
	virtual void EnableLoop(const bool isLoop);
	/**
	*@brief Get Speed
	*@return float Video Speed
	*/
	float GetSpeed() const;
};