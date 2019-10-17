#pragma once
#include "MovieImage.h"
#include "Timer\glTimer.h"
/**
*�{���Ǝ��Ԕ�΂��Ƀo�O
*/
class CImages : public CMovieImage
{
	float preTime;
	//! Movie Time
	CTime time;
	/**
	*@brief �o�^������
	*/
	void Entry() override;
	/**
	*@brief �X�V����
	*/
	void Update() override;
	/**
	*@brief �Đ�������
	*/
	void Play() override;
	/**
	*@brief �ꎞ��~����
	*/
	void Pause() override;
public:
	/**
	*@brief constructor
	*/
	explicit CImages();
	/**
	*@brief constructor
	*@param[in] string path File Path
	*@param[in] format movie Video Format
	*/
	explicit CImages(const std::string& path, const TFormat& movie);
	/**
	*@brief destructor
	*/
	virtual ~CImages();
	/**
	*@brief Movie Load
	*@param[in] string path File Path
	*@param[in] format movie Video Format
	*/
	bool Load(const std::string& path, const TFormat& movie);
	/**
	*@brief Set Movie Time
	*@param[in] float time Movie Time
	*/
	void SetTime(const float time) override;
	/**
	*@brief Set Movie Speed
	*@param[in] float speed Movie Speed
	*/
	void SetSpeed(const float speed) override;
	/**
	*@brief Get Movie Time
	*@return float Movie Time
	*/
	float GetTime();
};