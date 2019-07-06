#pragma once
#include "Sprite\Sprite.h"
#include "System\System.h"

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
protected:
	//! OpenCV�s��
	cv::Mat	mat;
	//! �L���v�`�����s��
	cv::VideoCapture videoCapture;
	//!�@�ǂݍ��񂾓���̃t���[�����[�g
	float videoFramerate;
	//! ����̍Đ����x�̔{��
	float magnification;
	//! ����̃��[�v�ݒ�
	bool loop;
	//! �Đ����
	bool enablePlay;
	//! �Đ��̑O���
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
	explicit MovieImage();
	/**
	*@brief destructor
	*/
	virtual ~MovieImage();
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