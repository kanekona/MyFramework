#include "Audio.h"
//---------------------------------
//@:Audioclass
//---------------------------------
Audio::Audio()
{
	//�A�v���P�[�V�������f�o�C�X�ɐڑ�������
	//�����̓f�o�C�X�̎w��,NULL�Ȃ����̃f�o�C�X
	this->device = alcOpenDevice(nullptr);
	if (!this->device)
	{
#ifdef KL_DEBUG
		std::cout << "�f�o�C�X�̐ڑ�Error" << std::endl;
#endif
		return;
	}
	//�R���e�L�X�g�̐���
	this->context = alcCreateContext(this->device, nullptr);
	if (!this->context)
	{
#ifdef KL_DEBUG
		std::cout << "�R���e�L�X�g����Error" << std::endl;
#endif
		return;
	}
	//���삷��R���e�L�X�g�̑I��
	if (alcMakeContextCurrent(this->context) == ALC_FALSE)
	{
#ifdef KL_DEBUG
		std::cout << "����R���e�L�X�g�̑I��Error" << std::endl;
#endif		
		return;
	}
}
Audio::~Audio()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}
//---------------------------------
//@:Bufferclass
//---------------------------------
Buffer::Buffer()
{
	//�o�b�t�@���P����
	alGenBuffers(1, &this->id);
	//���ݐi�s���Ԃ�0�ɂ���
	this->nowTime = 0.f;
}
Buffer::Buffer(const std::string& path_)
	:path(path_)
{
	//�o�b�t�@���P����
	alGenBuffers(1, &this->id);
	//Wav�t�@�C���̓ǂݍ���
	Wav wav_data(path_);
	//�o�ߎ��Ԃ��m�F
	this->nowTime = wav_data.time();
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// �g�`�f�[�^���o�b�t�@�ɃZ�b�g
	//BufferID,Format,�g�`�f�[�^,�T�C�Y,�T���v�����O���[�g
	Bind(wav_data.isStereo(), wav_data.data(), wav_data.size(), wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
Buffer::Buffer(const std::string& path_, const size_t& time)
	:path(path_)
{
	//�o�b�t�@���P����
	alGenBuffers(1, &this->id);
	//Wav�t�@�C���̓ǂݍ���
	Wav wav_data(path_);
	//�o�ߎ��Ԃ��m�F
	this->nowTime = wav_data.time();
	size_t num = time * wav_data.sampleRate()* wav_data.channel() * sizeof(uint16_t);
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// �g�`�f�[�^���o�b�t�@�ɃZ�b�g
	//BufferID,Format,�g�`�f�[�^,�T�C�Y,�T���v�����O���[�g
	Bind(wav_data.isStereo(), wav_data.data(num), wav_data.size() - (u_int)num, wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
Buffer::~Buffer()
{
	//�o�b�t�@�̍폜
	alDeleteBuffers(1, &this->id);
}
float Buffer::GetTime() const
{
	//�i�s���Ԃ�Ԃ�
	return this->nowTime;
}
ALuint Buffer::GetID() const
{
	//�o�b�t�@�ɓo�^���Ă���ID��Ԃ�
	return this->id;
}
void Buffer::Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const
{
	//�g�`�f�[�^���o�b�t�@�ɃZ�b�g
	alBufferData(this->id, stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, rate);
}
void Buffer::SetFrameBuffer(const size_t& num)
{
	Wav wav_data(path);
	Bind(wav_data.isStereo(), wav_data.data(num), wav_data.size() - (u_int)num, wav_data.sampleRate());
}
char Buffer::GetWaveform(const float time)
{
	return waveformData.at((unsigned int)(time * oneSecondsData));
}
//---------------------------------
//@:Sourceclass
//---------------------------------
Source::Source()
{
	//�\�[�X���P��������
	alGenSources(1, &this->id);
}
Source::~Source()
{
	//�g�`�f�[�^����������
	this->UnBindBuffer();
	//�\�[�X���폜����
	alDeleteSources(1, &this->id);
}
void Source::BindBuffer(const Buffer& burrer)
{
	//�\�[�X�Ƀo�b�t�@���w�肷��
	alSourcei(this->id, AL_BUFFER, burrer.GetID());
}
void Source::UnBindBuffer() const
{
	//�\�[�X�̃o�b�t�@����������
	alSourcei(this->id, AL_BUFFER, 0);
}
int Source::GetBufferID() const
{
	int bufferID;
	alGetSourcei(this->id, AL_BUFFER, &bufferID);
	return bufferID;
}
ALuint Source::GetID() const
{
	//�\�[�X��ID��Ԃ�
	return this->id;
}
void Source::Play() const
{
	//�Đ�����
	alSourcePlay(this->id);
}
void Source::Stop() const
{
	//�~�߂�
	alSourceStop(this->id);
}
void Source::Pause() const
{
	//�ꎞ��~����
	alSourcePause(this->id);
}
void Source::SetSourceRelative(const bool relative) const
{
	alSourcei(this->id, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);
}
int Source::GetSourceRelative() const
{
	int relative;
	alGetSourcei(this->id, AL_SOURCE_RELATIVE, &relative);
	return relative;
}
void Source::SetVolume(const float volume) const
{
	//���ʂ̕ύX
	alSourcef(this->id, AL_GAIN, volume);
}
void Source::SetPitch(const float value) const
{
	//�s�b�`�̕ύX
	alSourcef(this->id, AL_PITCH, value);
}
void Source::SetLoop(const bool loop) const
{
	//TRUE�ŏI�����ŏ��̈ʒu�ɖ߂�
	alSourcei(this->id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}
bool Source::IsPlay() const
{
	//���݂̏�Ԃ�Ԃ�
	ALint state;
	alGetSourcei(this->id, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
float Source::GetTime() const
{
	//���݂̍Đ����Ԃ�Ԃ�
	ALfloat nowtime;
	alGetSourcef(this->id, AL_SEC_OFFSET, &nowtime);
	return nowtime;
}
void Source::SetTime(const float time) const
{
	alSourcef(this->id, AL_SEC_OFFSET, time);
}
void Source::QueueBuffer(const Buffer& buffer) const
{
	ALuint buffers = buffer.GetID();
	//�o�b�t�@�l�[���̃L���[���쐬
	alSourceQueueBuffers(this->id, 1, &buffers);
}
ALuint Source::UnqueueBuffer() const
{
	ALuint buffers;
	//�L���[����o�b�t�@����������
	alSourceUnqueueBuffers(this->id, 1, &buffers);
	return buffers;
}
int Source::GetProcessed() const
{
	int pro_;
	//�Đ��ς݂̃o�b�t�@����Ԃ�
	alGetSourcei(this->id, AL_BUFFERS_PROCESSED, &pro_);
	return pro_;
}
int Source::GetQueued() const
{
	int queued;
	alGetSourcei(this->id, AL_BUFFERS_QUEUED, &queued);
	return queued;
}
float Source::GetPitch() const
{
	float pitch;
	alGetSourcef(this->id, AL_PITCH, &pitch);
	return pitch;
}
float Source::GetVolume() const
{
	float volume;
	alGetSourcef(this->id, AL_GAIN, &volume);
	return volume;
}
int Source::GetLoop() const
{
	int loop;
	alGetSourcei(this->id, AL_LOOPING, &loop);
	return loop;
}
int Source::GetSourceType() const
{
	int type;
	alGetSourcei(this->id, AL_SOURCE_TYPE, &type);
	return type;
}
void Source::SetReferenceDistance(const float distance) const
{
	alSourcef(this->id, AL_REFERENCE_DISTANCE, distance);
}
float Source::GetReferenceDistance() const
{
	float distance;
	alGetSourcef(this->id, AL_REFERENCE_DISTANCE, &distance);
	return distance;
}
void Source::SetRolloffFactor(const float factor) const
{
	alSourcef(this->id, AL_ROLLOFF_FACTOR, factor);
}
float Source::GetRolloffFactor() const
{
	float factor;
	alGetSourcef(this->id, AL_ROLLOFF_FACTOR, &factor);
	return factor;
}
void Source::SetPosition(const Vec3& position) const
{
	alSource3f(this->id, AL_POSITION, position.x, position.y, position.z);
}
Vec3 Source::GetPosition() const
{
	Vec3 position;
	alGetSource3f(this->id, AL_POSITION, &position.x, &position.y, &position.z);
	return position;
}
void Source::SetVelocity(const Vec3& velocity) const
{
	alSource3f(this->id, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
Vec3 Source::GetVelocity() const
{
	Vec3 velocity;
	alGetSource3f(this->id, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
void Source::SetDirection(const Vec3& direction) const
{
	alSource3f(this->id, AL_DIRECTION, direction.x, direction.y, direction.z);
}
Vec3 Source::GetDirection() const
{
	Vec3 direction;
	alGetSource3f(this->id, AL_DIRECTION, &direction.x, &direction.y, &direction.z);
	return direction;
}
void Source::SetConeInnerAngle(const float angle) const
{
	alSourcef(this->id, AL_CONE_INNER_ANGLE, angle);
}
float Source::GetConeInnerAngle() const
{
	float angle;
	alGetSourcef(this->id, AL_CONE_INNER_ANGLE, &angle);
	return angle;
}
void Source::SetConeOuterAngle(const float angle) const
{
	alSourcef(this->id, AL_CONE_OUTER_ANGLE, angle);
}
float Source::GetConeOuterAngle() const
{
	float angle;
	alGetSourcef(this->id, AL_CONE_OUTER_ANGLE, &angle);
	return angle;
}
void Source::SetConeOuterGain(const float volume) const
{
	alSourcef(this->id, AL_CONE_OUTER_GAIN, volume);
}
float Source::GetConeOuterGain() const
{
	float gain;
	alGetSourcef(this->id, AL_CONE_OUTER_GAIN, &gain);
	return gain;
}
void Source::SetOrientation(const float* orientation)
{
	alListenerfv(AL_ORIENTATION, orientation);
}
float* Source::GetOrientation(float* orientation)
{
	alGetListenerfv(AL_ORIENTATION, orientation);
	return orientation;	
}
void Source::SetListenerPosition(const Vec3& position)
{
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}
Vec3 Source::GetListenerPosition()
{
	Vec3 position;
	alGetListener3f(AL_POSITION, &position.x, &position.y, &position.z);
	return position;
}
void Source::SetListenerVelocity(const Vec3& velocity)
{
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
Vec3 Source::GetListenerVelocity()
{
	Vec3 velocity;
	alGetListener3f(AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
void Source::SetListenerGain(const float volume)
{
	alListenerf(AL_GAIN, volume);
}
float Source::GetListenerGain()
{
	float volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}
//---------------------------------
//@:Wavclass
//---------------------------------
Wav::Wav(const std::string& file)
{
	std::ifstream fstr(file, std::ios::binary);
	if (!fstr)
	{
#ifdef KL_DEBUG
		std::cout << "�t�@�C���ǂݍ��݃G���[" << std::endl;
#endif
		throw;
	}
	// �t�@�C���������
	if (!Wav::analyzeWavFile(this->info, fstr))
	{
#ifdef KL_DEBUG
		std::cout << "Wav�t�@�C���ǂݍ��݃G���[: " << file << std::endl;
#endif		
		throw;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// ID���P�ŗʎq���r�b�g����16�ȊO�͈���Ȃ�
#ifdef KL_DEBUG
		std::cout << "Wav�t�@�C���̃t�H�[�}�b�g�G���[" << std::endl;
#endif
		throw;
	}
	// �Đ�����(�b)
	this->time_ = this->info.size / this->info.ch / 2.0f / this->info.sample_rate;
	// �f�[�^�ǂݍ���
	data_.resize(this->info.size);
	Wav::searchChunk(fstr, "data");
	fstr.seekg(4, fstr.cur);
	fstr.read(&data_[0], info.size);
}
u_int Wav::channel() const
{
	return this->info.ch;
}
bool Wav::isStereo() const
{
	return this->info.ch == 2;
}
u_int Wav::sampleRate() const
{
	return this->info.sample_rate;
}
u_int Wav::size() const
{
	return this->info.size;
}
float Wav::time() const
{
	return this->time_;
}
const char* Wav::data() const
{
	return &this->data_[0];
}
const char* Wav::data(const size_t& number) const
{
	return &this->data_[number];
}
u_int Wav::getValue(const char* ptr, const u_int num)
{
	u_int value = 0;
	for (u_int i = 0; i < num; ++i, ++ptr)
	{
		// TIPS:int�^��菬�����^��int�^�Ɋg������Ă���v�Z�����̂�8bit�ȏ�V�t�g���Ă����Ȃ�
		value = value + (static_cast<u_char>(*ptr) << (i * 8));
	}
#ifdef __BIG_ENDIAN__
	value = (value << 24) | ((value << 8) & 0xff0000) | ((value >> 8) & 0xff00) | (value >> 24);
#endif
	return value;
}
bool Wav::searchChunk(std::ifstream& fstr, const char* chunk)
{
	//�`�����N�J�n�ʒu
	int WAV_START_SIZE = 12;
	fstr.seekg(WAV_START_SIZE, fstr.beg);
	// �`�����N�̕��т͕s��Ȃ̂ŁA��Ƀt�@�C���̐擪����T��
	while (1)
	{
		char tag[4];
		fstr.read(tag, 4);
		if (!std::strncmp(tag, chunk, 4))
		{
			return true;
		}
		// ���̃`�����N��
		char data[4];
		fstr.read(data, 4);
		u_int chunk_size = Wav::getValue(data, 4);
		fstr.seekg(chunk_size, fstr.cur);
		if (fstr.eof())
		{
			break;
		}
	}
	return false;
}
u_int Wav::getChunkSize(std::ifstream& fstr)
{
	char data[4];
	fstr.read(data, 4);
	return Wav::getValue(data, 4);
}
bool Wav::analyzeWavFile(Info& info, std::ifstream& fstr)
{
	// �t�@�C����wav�`�������ׂ�
	enum
	{
		WAV_HEADER_SIZE = 12
	};
	char header[WAV_HEADER_SIZE];
	fstr.read(header, WAV_HEADER_SIZE);
	if (std::strncmp(&header[0], "RIFF", 4))
	{
#ifdef KL_DEBUG
		std::cout << "���̃t�@�C����RIFF�ł͂���܂���" << std::endl;
#endif
		return false;
	}
	if (std::strncmp(&header[8], "WAVE", 4))
	{
#ifdef KL_DEBUG
		std::cout << "���̃t�@�C����Wave�ł͂���܂���" << std::endl;
#endif		
		return false;
	}
	enum
	{
		// fmt�`�����N���̃f�[�^�ʒu
		WAV_ID = 0,
		WAV_CH = WAV_ID + 2,
		WAV_SAMPLE_RATE = WAV_CH + 2,
		WAV_BPS = WAV_SAMPLE_RATE + 4,
		WAV_BLOCK_SIZE = WAV_BPS + 4,
		WAV_BIT = WAV_BLOCK_SIZE + 2,
	};
	// fmt�`�����N��T���ăf�[�^�`�����擾
	if (!searchChunk(fstr, "fmt "))
	{
#ifdef KL_DEBUG
		std::cout << "fmt�`�����N�����݂��܂���" << std::endl;
#endif
		return false;
	}
	u_int chunk_size = Wav::getChunkSize(fstr);
	std::vector<char> chunk(chunk_size);
	fstr.read(&chunk[0], chunk_size);
	info.id = Wav::getValue(&chunk[WAV_ID], 2);
	info.ch = Wav::getValue(&chunk[WAV_CH], 2);
	info.sample_rate = Wav::getValue(&chunk[WAV_SAMPLE_RATE], 4);
	info.bit = Wav::getValue(&chunk[WAV_BIT], 2);
	// data�`�����N��T���ăf�[�^�����擾
	if (!searchChunk(fstr, "data"))
	{
#ifdef KL_DEBUG
		std::cout << "data�`�����N�����݂��܂���" << std::endl;
#endif
		return false;
	}
	info.size = Wav::getChunkSize(fstr);
	return true;
}
std::vector<char> Wav::Getdata()
{
	return this->data_;
}
void Wav::TestFunction(const float value)
{
	for (auto it : data_)
	{
		it *= value;
	}
}
//---------------------------------
//@:StreamWavclass
//---------------------------------
StreamWav::StreamWav(const std::string& file) :
	fstr_(file, std::ios::binary),
	loop_(false)
{
	if (!this->fstr_) throw "�t�@�C�����J�����Ƃ��ł��܂���";
	// �t�@�C���������
	if (!Wav::analyzeWavFile(this->info, this->fstr_))
	{
		return;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// ID���P�ŗʎq���r�b�g����16�ȊO�͈���Ȃ�
#ifdef KL_DEBUG
		std::cout << "Wav�t�@�C���t�H�[�}�b�g�G���[" << std::endl;
#endif
		return;
	}
	this->last_size_ = this->info.size;
	// �f�[�^�̐擪�ʒu���o���Ă���
	this->top_pos_ = static_cast<size_t>(this->fstr_.tellg());
}
bool StreamWav::isStereo() const
{
	return this->info.ch == 2;
}
u_int StreamWav::sampleRate() const
{
	return this->info.sample_rate;
}
size_t StreamWav::GetlastSize() const
{
	return this->last_size_;
}
void StreamWav::loop(const bool loop)
{
	this->loop_ = loop;
}
void StreamWav::toTop()
{
	this->fstr_.seekg(this->top_pos_, this->fstr_.beg);
	this->last_size_ = this->info.size;
}
bool StreamWav::isEnd() const
{
	return last_size_ == 0;
}
size_t StreamWav::read(std::vector<char>& buffer)
{
	size_t remain_size = buffer.size();
	// ���[�v���Ȃ��ꍇ�A�c��̒��r���[�ȃT�C�Y��ǂݍ���ŏI��
	if (!this->loop_ && (this->last_size_ < remain_size))
	{
		remain_size = this->last_size_;
	}
	size_t offset = 0;
	size_t total_read_size = 0;
	// ���[�v�Đ��̏ꍇ�̓o�b�t�@�𖞂����܂Ńf�[�^��ǂݍ���
	while (remain_size > 0) {
		size_t read_size = StreamWav::readData(buffer, offset, remain_size);

		total_read_size += read_size;
		remain_size -= read_size;
		this->last_size_ -= read_size;
		offset += read_size;
		if (this->loop_ && !this->last_size_)
		{
			StreamWav::toTop();
		}
	}
	return total_read_size;
}
size_t StreamWav::readData(std::vector<char>& buffer, const size_t offset, const size_t size)
{
	size_t read_size = (size < this->last_size_) ? size : this->last_size_;
	this->fstr_.read(&buffer[offset], read_size);
	return read_size;
}