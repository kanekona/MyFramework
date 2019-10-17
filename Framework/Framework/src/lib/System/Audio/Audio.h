
#pragma once
#include "System\System.h"
/**
*@brief	デバイスを設定するためのclass
*/
class CAudio
{
	ALCdevice* device;
	ALCcontext*context;
public:
		CAudio();
		~CAudio();
};
/**
*@brief	SoundDataのBufferDataを扱う
*/
class CBuffer
{
public:
	explicit CBuffer();
	explicit CBuffer(const std::string& path_);
	explicit CBuffer(const std::string& path_, const size_t& time);
	virtual ~CBuffer();
	std::string path;
	ALuint id;
	float nowTime;
	float GetTime() const;
	ALuint GetID() const;
	void Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const;
	void SetFrameBuffer(const size_t& num);
	char GetWaveform(const float time);
	std::vector<char> waveformData;
	u_int sampleRate;
	unsigned int oneSecondsData;
};
/**
*@brief	SoundDataのSourceDataを扱う
*/
class CSource
{
public:
	CSource();
	~CSource();
	ALuint id;
	void BindBuffer(const CBuffer& buffer);
	void UnBindBuffer() const;
	int GetBufferID() const;
	ALuint GetID() const;
	void Play() const;
	void Stop() const;
	void Pause() const;
	bool IsPlay() const;
	void SetSourceRelative(const bool relative) const;
	int GetSourceRelative() const;
	void SetVolume(const float volume) const;
	float GetVolume() const;
	void SetPitch(const float value) const;
	float GetPitch() const;
	void SetLoop(const bool loop) const;
	int GetLoop() const;	
	void SetTime(const float time) const;
	float GetTime() const;
	void QueueBuffer(const CBuffer& buffer_) const;
	ALuint UnqueueBuffer() const;
	int GetProcessed() const;
	int GetQueued() const;
	int GetSourceType() const;
	void SetReferenceDistance(const float distance) const;
	float GetReferenceDistance() const;
	void SetRolloffFactor(const float factor) const;
	float GetRolloffFactor() const;
	void SetPosition(const CVec3& position) const;
	CVec3 GetPosition() const;
	void SetVelocity(const CVec3& velocity) const;
	CVec3 GetVelocity() const;
	void SetDirection(const CVec3& direction) const;
	CVec3 GetDirection() const;
	void SetConeInnerAngle(const float angle) const;
	float GetConeInnerAngle() const;
	void SetConeOuterAngle(const float angle) const;
	float GetConeOuterAngle() const;
	void SetConeOuterGain(const float volume) const;
	float GetConeOuterGain() const;
	static void SetOrientation(const float* orientation);
	static float* GetOrientation(float* orientation);
	static void SetListenerPosition(const CVec3& position);
	static CVec3 GetListenerPosition();
	static void SetListenerVelocity(const CVec3& velocity);
	static CVec3 GetListenerVelocity();
	static void SetListenerGain(const float volume);
	static float GetListenerGain();
};
/**
*@brief	Wavファイルのデータを扱う
*/
class CWav
{
public:
	struct Info {
		u_int id;
		u_int ch;
		u_int sample_rate;
		u_int bit;
		u_int size;
	};
	explicit CWav(const std::string& file);
	//チャンネル数を返す
	u_int channel() const;
	//データがステレオならtrueを返す
	bool isStereo() const;
	//サンプリングレートを返す
	u_int sampleRate() const;
	//データサイズを返す
	u_int size() const;
	//再生時間を返す
	float time() const;
	//波形データを返す
	const char* data() const;
	//指定箇所の波形データを返す
	const char* data(const size_t& number) const;
	//wavの情報を取得
	static bool analyzeWavFile(Info& info, std::ifstream& fstr);
	//波形データを取得する
	std::vector<char> Getdata();
	//波形データに倍率をかける
	void TestFunction(const float value);
private:
	Info info;
	float time_;
	std::vector<char> data_;
	//指定バイト数のメモリの内容をint値にする
	static u_int getValue(const char* ptr, const u_int num);
	//wavの指定チャンクを探す
	static bool searchChunk(std::ifstream& fstr, const char* chunk);
	//チャンクのサイズを取得
	static u_int getChunkSize(std::ifstream& fstr);
};
class CStreamWav {
public:
	explicit CStreamWav(const std::string& file);
	bool isStereo() const;
	u_int sampleRate() const;
	void loop(const bool loop);
	//再生位置を先頭に戻す
	void toTop();
	bool isEnd() const;
	size_t GetlastSize() const;
	//再生バッファにデータを読み込む
	size_t read(std::vector<char>& buffer);
private:
	std::ifstream fstr_;
	CWav::Info info;
	size_t top_pos_;
	bool loop_;
	size_t last_size_;
	//ファイルからバッファへデータを読み込む
	size_t readData(std::vector<char>& buffer, const size_t offset, const size_t size);
};