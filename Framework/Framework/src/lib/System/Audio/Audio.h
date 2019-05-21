
#pragma once
#include "System\System.h"
/**
*@brief	�f�o�C�X��ݒ肷�邽�߂�class
*/
class Audio
{
	ALCdevice* device;
	ALCcontext*context;
public:
		Audio();
		~Audio();
};
/**
*@brief	SoundData��BufferData������
*/
class Buffer
{
public:
	explicit Buffer();
	explicit Buffer(const std::string& path_);
	explicit Buffer(const std::string& path_, const size_t& time);
	virtual ~Buffer();
	std::string path;
	ALuint id_;
	float nowTime;
	float GetTime() const;
	ALuint GetID() const;
	void Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const;
	void SetFrameBuffer(const size_t& num);
	std::vector<char> waveformData;
	u_int sampleRate;
};
/**
*@brief	SoundData��SourceData������
*/
class Source
{
public:
	Source();
	~Source();
	ALuint id_;
	void BindBuffer(const Buffer& buffer_);
	void UnBindBuffer() const;
	ALuint GetID() const;
	void Play() const;
	void Stop() const;
	void Pause() const;
	void Volume(const float volume_) const;
	void Pitch(const float value_) const;
	void Looping(const bool loop_) const;
	void SetTime(const float time) const;
	bool IsPlay() const;
	float CurrentTime() const;
	void QueueBuffer(const Buffer& buffer_) const;
	ALuint UnqueueBuffer() const;
	int Processed() const;
};
/**
*@brief	Wav�t�@�C���̃f�[�^������
*/
class Wav
{
public:
	struct Info {
		u_int id;
		u_int ch;
		u_int sample_rate;
		u_int bit;
		u_int size;
	};
	explicit Wav(const std::string& file);
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
class StreamWav {
public:
	explicit StreamWav(const std::string& file);
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
	Wav::Info info;
	size_t top_pos_;
	bool loop_;
	size_t last_size_;
	//�t�@�C������o�b�t�@�փf�[�^��ǂݍ���
	size_t readData(std::vector<char>& buffer, const size_t offset, const size_t size);
};