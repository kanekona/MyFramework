#pragma once
#include "MovieImage.h"
#include "Timer\glTimer.h"
/**
*倍速と時間飛ばしにバグ
*/
class Images : public MovieImage
{
	float preTime;
	//! Movie Time
	Time time;
	/**
	*@brief 登録時処理
	*/
	void Enter() override;
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