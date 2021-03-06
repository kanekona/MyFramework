
#pragma once
#include "Audio.h"
/**
*サウンドを読み込み、再生を行うclass
*
*一括読み込みをしている
*/
class CSound
{
private:
	//! ループ再生
	bool isloop_;
	//! 音量
	float volume_;
	//! 1秒の波形データ量
	unsigned int oneSecondWaveformData;
	//! 全波形データ量
	unsigned int allWaveformData;
	//! 現在のファイルパス
	std::string path;
	//! bufferData
	std::shared_ptr<CBuffer> buffer;
	//! sourceData
	std::shared_ptr<CSource> source;
public:
	/**
	*@brief	constructor
	*/
	explicit CSound();
	/**
	*@brief	constructor
	*@param[in]	string path_ ファイルのパス
	*@param[in]	bool loop ループ再生
	*/
	explicit CSound(const std::string& path_, const bool loop = false);
	/**
	*brief	destructor
	*/
	virtual ~CSound();
	/**
	*@brief	サウンドの読み込み
	*@param[in]	string path_ ファイル名
	*@param[in]	bool loop ループ再生
	*@return bool 読み込み成功true
	*/
	bool Create(const std::string& path_, const bool loop = false);
	/**
	*@brief	サウンドの再生
	*/
	void Play() const;
	/**
	*@brief	サウンドの停止
	*/
	void Stop() const;
	/**
	*@brief	サウンドの一時停止
	*/
	void Pause() const;
	/**
	*@brief	サウンドの音量変更
	*@param[in]	float value_ 音量
	*/
	void Volume(const float value_) const;
	/**
	*@brief	サウンドのピッチ変更
	*@param[in]	floar value_ ピッチ
	*/
	void Pitch(const float value_) const;
	/**
	*@brief	サウンドのループ再生
	*@param[in]	bool loop_ ループの設定
	*/
	void Looping(const bool loop_) const;
	/**
	*@brief	サウンドが再生中か調べる
	*@return 再生中true
	*/
	bool IsPlay() const;
	/**
	*@brief	現在の再生時間を返す
	*@return 現在の再生時間
	*/
	float CurrentTime() const;
	/**
	*@brief	サウンドの時間を返す
	*@return サウンドの時間
	*/
	float Duration() const;
	/**
	*@brief	最大音量を指定する
	*@param[in]	float maxVolume_ 最大音量
	*/
	void SetVolume(float maxVolume_);
	/**
	*@brief	設定されている最大音量を返す
	*@return float 最大音量
	*/
	float GetVolume() const;
	/**
	*@brief Get Buffer
	*@return Buffer* BufferPtr
	*/
	CBuffer* GetBuffer() const;
	/**
	*@brief Get Source
	*@return Source* SourcePtr
	*/
	CSource* GetSource() const;
	/*
	*@brief	指定フレームへスキップする
	*@param[in] time スキップする再生時間
	*/
	void Skip(const float time);
#if ENGINE_DEBUG
	void Test();
#endif //ENGINE_DEBUG
};