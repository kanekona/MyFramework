
#pragma once
#include "Audio.h"
#include <mutex>
///サウンドの読み込み、再生を行うclass
///随時読み込み
///※バグあり
class CStreamingSound {
private:
	enum {
		BUFFER_NUM = 2,
		SLEEP_TIME_MS = 250
	};
	std::shared_ptr<CSource> source_;
	bool pause_;
	// 再生用のスレッドとの連携
	struct Param {
		std::mutex mutex;
		bool stopped;
		Param() :stopped(false) {}
		bool backStartPos;
		bool DeleteThread;
	};
	std::shared_ptr<Param> param_;
	std::string filepath_;
	bool loop_;
	bool isplay_;
public:
	CStreamingSound();
	CStreamingSound(const std::string& path, const bool loop = false);
	void gain(const float gain);
	void pause();
	void play();
	void pitch(const float value_) const;
	void stop();
	void DeleteSound();
	bool isPlaying();
	float GetTime() const;
#ifdef KL_DEBUG
	void debugUpdata();
#endif
	void createSound(const std::string& path, bool loop = false);
private:
	static void queueStream(CStreamWav& stream, CSource &source, CBuffer& buffer, std::vector<char>& sound_buffer);
	static void streamProc(const std::string& path, const bool loop, std::shared_ptr<CSource>& source, std::shared_ptr<Param>& param);
};