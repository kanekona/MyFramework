#include "Audio.h"
//---------------------------------
//@:Audioclass
//---------------------------------
Audio::Audio()
{
	//アプリケーションをデバイスに接続させる
	//引数はデバイスの指定,NULLなら既定のデバイス
	this->device = alcOpenDevice(nullptr);
	if (!this->device)
	{
#ifdef KL_DEBUG
		std::cout << "デバイスの接続Error" << std::endl;
#endif
		return;
	}
	//コンテキストの生成
	this->context = alcCreateContext(this->device, nullptr);
	if (!this->context)
	{
#ifdef KL_DEBUG
		std::cout << "コンテキスト生成Error" << std::endl;
#endif
		return;
	}
	//操作するコンテキストの選択
	if (alcMakeContextCurrent(this->context) == ALC_FALSE)
	{
#ifdef KL_DEBUG
		std::cout << "操作コンテキストの選択Error" << std::endl;
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
	//バッファを１つ生成
	alGenBuffers(1, &this->id);
	//現在進行時間を0にする
	this->nowTime = 0.f;
}
Buffer::Buffer(const std::string& path_)
	:path(path_)
{
	//バッファを１つ生成
	alGenBuffers(1, &this->id);
	//Wavファイルの読み込み
	Wav wav_data(path_);
	//経過時間を確認
	this->nowTime = wav_data.time();
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// 波形データをバッファにセット
	//BufferID,Format,波形データ,サイズ,サンプリングレート
	Bind(wav_data.isStereo(), wav_data.data(), wav_data.size(), wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
Buffer::Buffer(const std::string& path_, const size_t& time)
	:path(path_)
{
	//バッファを１つ生成
	alGenBuffers(1, &this->id);
	//Wavファイルの読み込み
	Wav wav_data(path_);
	//経過時間を確認
	this->nowTime = wav_data.time();
	size_t num = time * wav_data.sampleRate()* wav_data.channel() * sizeof(uint16_t);
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// 波形データをバッファにセット
	//BufferID,Format,波形データ,サイズ,サンプリングレート
	Bind(wav_data.isStereo(), wav_data.data(num), wav_data.size() - (u_int)num, wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
Buffer::~Buffer()
{
	//バッファの削除
	alDeleteBuffers(1, &this->id);
}
float Buffer::GetTime() const
{
	//進行時間を返す
	return this->nowTime;
}
ALuint Buffer::GetID() const
{
	//バッファに登録してあるIDを返す
	return this->id;
}
void Buffer::Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const
{
	//波形データをバッファにセット
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
	//ソースを１つ生成する
	alGenSources(1, &this->id);
}
Source::~Source()
{
	//波形データを解除する
	this->UnBindBuffer();
	//ソースを削除する
	alDeleteSources(1, &this->id);
}
void Source::BindBuffer(const Buffer& burrer)
{
	//ソースにバッファを指定する
	alSourcei(this->id, AL_BUFFER, burrer.GetID());
}
void Source::UnBindBuffer() const
{
	//ソースのバッファを解除する
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
	//ソースのIDを返す
	return this->id;
}
void Source::Play() const
{
	//再生する
	alSourcePlay(this->id);
}
void Source::Stop() const
{
	//止める
	alSourceStop(this->id);
}
void Source::Pause() const
{
	//一時停止する
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
	//音量の変更
	alSourcef(this->id, AL_GAIN, volume);
}
void Source::SetPitch(const float value) const
{
	//ピッチの変更
	alSourcef(this->id, AL_PITCH, value);
}
void Source::SetLoop(const bool loop) const
{
	//TRUEで終了時最初の位置に戻る
	alSourcei(this->id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}
bool Source::IsPlay() const
{
	//現在の状態を返す
	ALint state;
	alGetSourcei(this->id, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
float Source::GetTime() const
{
	//現在の再生時間を返す
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
	//バッファネームのキューを作成
	alSourceQueueBuffers(this->id, 1, &buffers);
}
ALuint Source::UnqueueBuffer() const
{
	ALuint buffers;
	//キューからバッファを除去する
	alSourceUnqueueBuffers(this->id, 1, &buffers);
	return buffers;
}
int Source::GetProcessed() const
{
	int pro_;
	//再生済みのバッファ数を返す
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
		std::cout << "ファイル読み込みエラー" << std::endl;
#endif
		throw;
	}
	// ファイル情報を解析
	if (!Wav::analyzeWavFile(this->info, fstr))
	{
#ifdef KL_DEBUG
		std::cout << "Wavファイル読み込みエラー: " << file << std::endl;
#endif		
		throw;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
#ifdef KL_DEBUG
		std::cout << "Wavファイルのフォーマットエラー" << std::endl;
#endif
		throw;
	}
	// 再生時間(秒)
	this->time_ = this->info.size / this->info.ch / 2.0f / this->info.sample_rate;
	// データ読み込み
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
		// TIPS:int型より小さい型はint型に拡張されてから計算されるので8bit以上シフトしても問題ない
		value = value + (static_cast<u_char>(*ptr) << (i * 8));
	}
#ifdef __BIG_ENDIAN__
	value = (value << 24) | ((value << 8) & 0xff0000) | ((value >> 8) & 0xff00) | (value >> 24);
#endif
	return value;
}
bool Wav::searchChunk(std::ifstream& fstr, const char* chunk)
{
	//チャンク開始位置
	int WAV_START_SIZE = 12;
	fstr.seekg(WAV_START_SIZE, fstr.beg);
	// チャンクの並びは不定なので、常にファイルの先頭から探す
	while (1)
	{
		char tag[4];
		fstr.read(tag, 4);
		if (!std::strncmp(tag, chunk, 4))
		{
			return true;
		}
		// 次のチャンクへ
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
	// ファイルがwav形式か調べる
	enum
	{
		WAV_HEADER_SIZE = 12
	};
	char header[WAV_HEADER_SIZE];
	fstr.read(header, WAV_HEADER_SIZE);
	if (std::strncmp(&header[0], "RIFF", 4))
	{
#ifdef KL_DEBUG
		std::cout << "このファイルはRIFFではありません" << std::endl;
#endif
		return false;
	}
	if (std::strncmp(&header[8], "WAVE", 4))
	{
#ifdef KL_DEBUG
		std::cout << "このファイルはWaveではありません" << std::endl;
#endif		
		return false;
	}
	enum
	{
		// fmtチャンク内のデータ位置
		WAV_ID = 0,
		WAV_CH = WAV_ID + 2,
		WAV_SAMPLE_RATE = WAV_CH + 2,
		WAV_BPS = WAV_SAMPLE_RATE + 4,
		WAV_BLOCK_SIZE = WAV_BPS + 4,
		WAV_BIT = WAV_BLOCK_SIZE + 2,
	};
	// fmtチャンクを探してデータ形式を取得
	if (!searchChunk(fstr, "fmt "))
	{
#ifdef KL_DEBUG
		std::cout << "fmtチャンクが存在しません" << std::endl;
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
	// dataチャンクを探してデータ長を取得
	if (!searchChunk(fstr, "data"))
	{
#ifdef KL_DEBUG
		std::cout << "dataチャンクが存在しません" << std::endl;
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
	if (!this->fstr_) throw "ファイルを開くことができません";
	// ファイル情報を解析
	if (!Wav::analyzeWavFile(this->info, this->fstr_))
	{
		return;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
#ifdef KL_DEBUG
		std::cout << "Wavファイルフォーマットエラー" << std::endl;
#endif
		return;
	}
	this->last_size_ = this->info.size;
	// データの先頭位置を覚えておく
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
	// ループしない場合、残りの中途半端なサイズを読み込んで終了
	if (!this->loop_ && (this->last_size_ < remain_size))
	{
		remain_size = this->last_size_;
	}
	size_t offset = 0;
	size_t total_read_size = 0;
	// ループ再生の場合はバッファを満たすまでデータを読み込む
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