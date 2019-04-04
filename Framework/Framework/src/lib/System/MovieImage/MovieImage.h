#pragma once
#include "Texture\Texture.h"
#include "Timer\glTimer.h"
#include "FPS\FPS.h"
#include "Audio\Sound.h"
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
/**
*@brief 童画の読み込みと再生と保存を行うclass
*/
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
	//! 更新にFPSclassを使用し、deltaTimeで計算する
	FPS* fps;
	//! 指定動画の音声データ
	Sound* sound;
	//! 動画のループ設定
	bool loop;
	//! 再生状態
	bool enablePlay;
	//! 再生の前状態
	bool preEnablePlay;
	/**
	*@brief 固定初期化
	*/
	void Init();
	/**
	*@brief	更新処理
	*基本的には毎フレーム行う
	*/
	void Update() override;
	/**
	*@brief 登録時処理
	*/
	void Enter() override;

	void Draw() override;
public:
	/**
	*@brief	DefaultConstructor
	*/
	explicit MovieImage();
	/**
	*@brief	constructor
	*@param[in] std::string filePath VideoFilePath
	*/
	explicit MovieImage(const std::string& filePath, const format& movie, const format& sound);
	/**
	*@brief	LoadVideoFile
	*@param[in] std::string filePath VideoFilePath
	*/
	bool Load(const std::string& filePath, const format& movie, const format& sound);
	/**
	*@brief	destructor
	*/
	virtual ~MovieImage();
	/**
	*@brief	Soundデータの取得
	*@param[in] std::string filePath soundFilePath
	*/
	void SoundLoad(const std::string& filePath);
	/**
	*@brief	ループ設定を行う
	*@param[in] bool isLoop enableLoop
	*/
	void EnableLoop(const bool isLoop);
	/**
	*@brief 再生設定を行う
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
};
