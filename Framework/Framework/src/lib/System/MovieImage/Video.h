#pragma once
#include "Audio\Sound.h"
#include "MovieImage.h"
/**
*@
*/

/**
*@brief 童画の読み込みと再生と保存を行うclass
*/
//class Video : public Sprite
//{
//	//! OpenCV行列
//	cv::Mat	mat;
//	//! キャプチャを行う
//	cv::VideoCapture videoCapture;
//	//!　読み込んだ動画のフレームレート
//	float videoFramerate;
//	//! 動画の再生速度の倍率
//	float magnification;
//	//! 指定動画の音声データ
//	Sound sound;
//	//! 動画のループ設定
//	bool loop;
//	//! 再生状態
//	bool enablePlay;
//	//! 再生の前状態
//	bool preEnablePlay;
//	/**
//	*@brief 固定初期化
//	*/
//	void Init();
//	/**
//	*@brief	更新処理
//	*基本的には毎フレーム行う
//	*/
//	void Update() override;
//	/**
//	*@brief 登録時処理
//	*/
//	void Entry() override;
//	/**
//	*@brief サウンドと動画の再生速度を登録する
//	*/
//	void SetSpeed();
//	/**
//	*@brief 映像の位置を音に合わせる
//	*/
//	void MatchMovieAndSound();
//	/**
//	*@brief フレームレートで更新を行う
//	*/
//	void AlignMovieWithFPS();
//public:
//	/**
//	*@brief	DefaultConstructor
//	*/
//	explicit Video();
//	/**
//	*@brief	constructor
//	*@param[in] std::string filePath VideoFilePath
//	*/
//	explicit Video(const std::string& filePath, const format& movie, const format& sound);
//	/**
//	*@brief	LoadVideoFile
//	*@param[in] std::string filePath VideoFilePath
//	*/
//	bool Load(const std::string& filePath, const format& movie, const format& sound);
//	/**
//	*@brief	destructor
//	*/
//	virtual ~Video();
//	/**
//	*@brief	Soundデータの取得
//	*@param[in] std::string filePath soundFilePath
//	*/
//	void SoundLoad(const std::string& filePath);
//	/**
//	*@brief	ループ設定を行う
//	*@param[in] bool isLoop enableLoop
//	*/
//	void EnableLoop(const bool isLoop);
//	/**
//	*@brief 再生設定を行う
//	*@param[in] bool isPlay enablePlay
//	*/
//	void SetPlay(const bool isPlay);
//	/**
//	*@brief	Set Movie Volume
//	*@param[in] float volume Volume
//	*/
//	void SetVolume(const float volume);
//	/**
//	*@brief	Set Movie Speed
//	*@param[in] float value Magnification
//	*/
//	void Speed(const float value);
//	/**
//	*@brief Get Movie Speed
//	*@return float Movie Speed Magnification
//	*/
//	float GetSpeed() const;
//	/**
//	*@brief Set Time
//	*@param[in] float time MovieTime
//	*/
//	void SetTime(const float time);
//	/**
//	*@brief Get Time
//	*@return float Movie Now Time
//	*/
//	float GetTime() const;
//};

class CVideo : public CMovieImage
{
	//! 音データ
	CSound sound;
	/**
	*@brief サウンドの読み込み
	*@param[in] string path FilePath
	*/
	void LoadSound(const std::string& path);
	/**
	*@brief 登録されたときに呼ばれる
	*/
	void Entry() override;
	/**
	*@brief 更新処理
	*/
	void Update() override;
	/**
	*@brief 再生時の処理
	*/
	void Play() override;
	/**
	*@brief 一時停止時の処理
	*/
	void Pause() override;
public:
	/**
	*@brief constructor
	*/
	explicit CVideo();
	/**
	*@brief constructor
	*@param[in] string path FilePath
	*@param[in] format movie Movie Format
	*@param[in] format sound Sound Format
	*/
	explicit CVideo(const std::string& path, const TFormat& movie, const TFormat& sound);
	/**
	*@brief destructor
	*/
	virtual ~CVideo();
	/**
	*@brief Video And Sound Load
	*@param[in] string path FilePath
	*@param[in] format movie Movie Format
	*@param[in] format sound Sound Format
	*/
	bool Load(const std::string& filePath, const TFormat& movie, const TFormat& sound);
	/**
	*@brief 音量設定
	*@param[in] float volume Sound Volume
	*/
	void SetVolume(const float volume);
	/**
	*@brief Sound Speed
	*@param[in] float speed Sound Speed
	*/
	void SetSpeed(const float speed) override;
	/**
	*@brief Current Time
	*@return float Video Current Time
	*/
	float GetTime() const;
	/**
	*@brief Video Set Time
	*@param[in] float time Video Time
	*/
	void SetTime(const float time) override;
};