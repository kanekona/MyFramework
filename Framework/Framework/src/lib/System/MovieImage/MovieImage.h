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