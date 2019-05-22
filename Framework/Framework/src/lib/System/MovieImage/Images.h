#pragma once
#include "MovieImage.h"
#include "Timer\glTimer.h"
/**
*�{���Ǝ��Ԕ�΂��Ƀo�O
*/
class Images : public MovieImage
{
	//! Movie Time
	Time time;
	/**
	*@brief �o�^������
	*/
	void Enter() override;
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
	explicit Images();
	/**
	*@brief constructor
	*@param[in] string path File Path
	*@param[in] format movie Video Format
	*/
	explicit Images(const std::string& path, const format& movie);
	/**
	*@brief destructor
	*/
	virtual ~Images();
	/**
	*@brief Movie Load
	*@param[in] string path File Path
	*@param[in] format movie Video Format
	*/
	bool Load(const std::string& path, const format& movie);
	/**
	*@brief Set Movie Time
	*@param[in] float time Movie Time
	*/
	void SetTime(const float time) override;
	/**
	*@brief Get Movie Time
	*@return float Movie Time
	*/
	float GetTime();
};