
#pragma once
#include "System\System.h"
/**
*@brief	�f�o�C�X��ݒ肷�邽�߂�class
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
*@brief	SoundData��BufferData������
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
*@brief	SoundData��SourceData������
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
*@brief	Wav�t�@�C���̃f�[�^������
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
	//�`�����l������Ԃ�
	u_int channel() const;
	//�f�[�^���X�e���I�Ȃ�true��Ԃ�
	bool isStereo() const;
	//�T���v�����O���[�g��Ԃ�
	u_int sampleRate() const;
	//�f�[�^�T�C�Y��Ԃ�
	u_int size() const;
	//�Đ����Ԃ�Ԃ�
	float time() const;
	//�g�`�f�[�^��Ԃ�
	const char* data() const;
	//�w��ӏ��̔g�`�f�[�^��Ԃ�
	const char* data(const size_t& number) const;
	//wav�̏����擾
	static bool analyzeWavFile(Info& info, std::ifstream& fstr);
	//�g�`�f�[�^���擾����
	std::vector<char> Getdata();
	//�g�`�f�[�^�ɔ{����������
	void TestFunction(const float value);
private:
	Info info;
	float time_;
	std::vector<char> data_;
	//�w��o�C�g���̃������̓��e��int�l�ɂ���
	static u_int getValue(const char* ptr, const u_int num);
	//wav�̎w��`�����N��T��
	static bool searchChunk(std::ifstream& fstr, const char* chunk);
	//�`�����N�̃T�C�Y���擾
	static u_int getChunkSize(std::ifstream& fstr);
};
class CStreamWav {
public:
	explicit CStreamWav(const std::string& file);
	bool isStereo() const;
	u_int sampleRate() const;
	void loop(const bool loop);
	//�Đ��ʒu��擪�ɖ߂�
	void toTop();
	bool isEnd() const;
	size_t GetlastSize() const;
	//�Đ��o�b�t�@�Ƀf�[�^��ǂݍ���
	size_t read(std::vector<char>& buffer);
private:
	std::ifstream fstr_;
	CWav::Info info;
	size_t top_pos_;
	bool loop_;
	size_t last_size_;
	//�t�@�C������o�b�t�@�փf�[�^��ǂݍ���
	size_t readData(std::vector<char>& buffer, const size_t offset, const size_t size);
};