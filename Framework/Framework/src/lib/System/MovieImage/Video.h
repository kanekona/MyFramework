#pragma once
#include "Audio\Sound.h"
#include "Sprite\Sprite.h"

/**
*@
*/

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

/**
*@brief ����̓ǂݍ��݂ƍĐ��ƕۑ����s��class
*/
class Video : public Sprite
{
	//! OpenCV�s��
	cv::Mat	mat;
	//! �L���v�`�����s��
	cv::VideoCapture videoCapture;
	//!�@�ǂݍ��񂾓���̃t���[�����[�g
	float videoFramerate;
	//! ����̍Đ����x�̔{��
	float magnification;
	//! �w�蓮��̉����f�[�^
	Sound sound;
	//! ����̃��[�v�ݒ�
	bool loop;
	//! �Đ����
	bool enablePlay;
	//! �Đ��̑O���
	bool preEnablePlay;
	/**
	*@brief �Œ菉����
	*/
	void Init();
	/**
	*@brief	�X�V����
	*��{�I�ɂ͖��t���[���s��
	*/
	void Update() override;
	/**
	*@brief �o�^������
	*/
	void Enter() override;
	/**
	*@brief �T�E���h�Ɠ���̍Đ����x��o�^����
	*/
	void SetSpeed();
	/**
	*@brief �f���̈ʒu�����ɍ��킹��
	*/
	void MatchMovieAndSound();
	/**
	*@brief �t���[�����[�g�ōX�V���s��
	*/
	void AlignMovieWithFPS();
public:
	/**
	*@brief	DefaultConstructor
	*/
	explicit Video();
	/**
	*@brief	constructor
	*@param[in] std::string filePath VideoFilePath
	*/
	explicit Video(const std::string& filePath, const format& movie, const format& sound);
	/**
	*@brief	LoadVideoFile
	*@param[in] std::string filePath VideoFilePath
	*/
	bool Load(const std::string& filePath, const format& movie, const format& sound);
	/**
	*@brief	destructor
	*/
	virtual ~Video();
	/**
	*@brief	Sound�f�[�^�̎擾
	*@param[in] std::string filePath soundFilePath
	*/
	void SoundLoad(const std::string& filePath);
	/**
	*@brief	���[�v�ݒ���s��
	*@param[in] bool isLoop enableLoop
	*/
	void EnableLoop(const bool isLoop);
	/**
	*@brief �Đ��ݒ���s��
	*@param[in] bool isPlay enablePlay
	*/
	void SetPlay(const bool isPlay);
	/**
	*@brief	Set Movie Volume
	*@param[in] float volume Volume
	*/
	void SetVolume(const float volume);
	/**
	*@brief	Set Movie Speed
	*@param[in] float value Magnification
	*/
	void Speed(const float value);
	/**
	*@brief Get Movie Speed
	*@return float Movie Speed Magnification
	*/
	float GetSpeed() const;
	/**
	*@brief Set Time
	*@param[in] float time MovieTime
	*/
	void SetTime(const float time);
	/**
	*@brief Get Time
	*@return float Movie Now Time
	*/
	float GetTime() const;
};
