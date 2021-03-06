#pragma once
#include "MovieImage.h"
#include "Timer\glTimer.h"
/**
*倍速と時間飛ばしにバグ
*/
class CImages : public CMovieImage
{
	float preTime;
	//! Movie Time
	CTime time;
	/**
	*@brief 登録時処理
	*/
	void Entry() override;
	/**
	*@brief 更新処理
	*/
	void Update() override;
	/**
	*@brief 再生時処理
	*/
	void Play() override;
	/**
	*@brief 一時停止処理
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