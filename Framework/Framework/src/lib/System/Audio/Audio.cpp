#include "Audio.h"
#include "Engine\EngineMacro.h"
//---------------------------------
//@:Audioclass
//---------------------------------
CAudio::CAudio()
{
	//アプリケーションをデバイスに接続させる
	//引数はデバイスの指定,NULLなら既定のデバイス
	device = alcOpenDevice(nullptr);
	if (!device)
	{
#ifdef KL_DEBUG
		std::cout << "デバイスの接続Error" << std::endl;
#endif
		return;
	}
	//コンテキストの生成
	context = alcCreateContext(device, nullptr);
	if (!context)
	{
#ifdef KL_DEBUG
		std::cout << "コンテキスト生成Error" << std::endl;
#endif
		return;
	}
	//操作するコンテキストの選択
	if (alcMakeContextCurrent(context) == ALC_FALSE)
	{
#ifdef KL_DEBUG
		std::cout << "操作コンテキストの選択Error" << std::endl;
#endif		
		return;
	}
}
CAudio::~CAudio()
{
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
//---------------------------------
//@:Bufferclass
//---------------------------------
CBuffer::CBuffer()
{
	//バッファを１つ生成
	alGenBuffers(1, &id);
	//現在進行時間を0にする
	nowTime = 0.f;
}
CBuffer::CBuffer(const std::string& path_)
	:path(path_)
{
	//バッファを１つ生成
	alGenBuffers(1, &id);
	//Wavファイルの読み込み
	CWav wav_data(path_);
	//経過時間を確認
	nowTime = wav_data.time();
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// 波形データをバッファにセット
	//BufferID,Format,波形データ,サイズ,サンプリングレート
	Bind(wav_data.isStereo(), wav_data.data(), wav_data.size(), wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
CBuffer::CBuffer(const std::string& path_, const size_t& time)
	:path(path_)
{
	//バッファを１つ生成
	alGenBuffers(1, &id);
	//Wavファイルの読み込み
	CWav wav_data(path_);
	//経過時間を確認
	nowTime = wav_data.time();
	size_t num = time * wav_data.sampleRate()* wav_data.channel() * sizeof(uint16_t);
	oneSecondsData = wav_data.sampleRate() * wav_data.channel() * sizeof(uint16_t);
	// 波形データをバッファにセット
	//BufferID,Format,波形データ,サイズ,サンプリングレート
	Bind(wav_data.isStereo(), wav_data.data(num), wav_data.size() - (u_int)num, wav_data.sampleRate());
	waveformData = wav_data.Getdata();
	sampleRate = wav_data.sampleRate();
}
CBuffer::~CBuffer()
{
	//バッファの削除
	alDeleteBuffers(1, &id);
}
float CBuffer::GetTime() const
{
	//進行時間を返す
	return nowTime;
}
ALuint CBuffer::GetID() const
{
	//バッファに登録してあるIDを返す
	return id;
}
void CBuffer::Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const
{
	//波形データをバッファにセット
	alBufferData(id, stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, rate);
}
void CBuffer::SetFrameBuffer(const size_t& num)
{
	CWav wav_data(path);
	Bind(wav_data.isStereo(), wav_data.data(num), wav_data.size() - (u_int)num, wav_data.sampleRate());
}
char CBuffer::GetWaveform(const float time)
{
	return waveformData.at((unsigned int)(time * oneSecondsData));
}
//---------------------------------
//@:Sourceclass
//---------------------------------
CSource::CSource()
{
	//ソースを１つ生成する
	alGenSources(1, &id);
}
CSource::~CSource()
{
	//波形データを解除する
	UnBindBuffer();
	//ソースを削除する
	alDeleteSources(1, &id);
}
void CSource::BindBuffer(const CBuffer& burrer)
{
	//ソースにバッファを指定する
	alSourcei(id, AL_BUFFER, burrer.GetID());
}
void CSource::UnBindBuffer() const
{
	//ソースのバッファを解除する
	alSourcei(id, AL_BUFFER, 0);
}
int CSource::GetBufferID() const
{
	int bufferID;
	alGetSourcei(id, AL_BUFFER, &bufferID);
	return bufferID;
}
ALuint CSource::GetID() const
{
	//ソースのIDを返す
	return id;
}
void CSource::Play() const
{
	//再生する
	alSourcePlay(id);
}
void CSource::Stop() const
{
	//止める
	alSourceStop(id);
}
void CSource::Pause() const
{
	//一時停止する
	alSourcePause(id);
}
void CSource::SetSourceRelative(const bool relative) const
{
	alSourcei(id, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);
}
int CSource::GetSourceRelative() const
{
	int relative;
	alGetSourcei(id, AL_SOURCE_RELATIVE, &relative);
	return relative;
}
void CSource::SetVolume(const float volume) const
{
	//音量の変更
	alSourcef(id, AL_GAIN, volume);
}
void CSource::SetPitch(const float value) const
{
	//ピッチの変更
	alSourcef(id, AL_PITCH, value);
}
void CSource::SetLoop(const bool loop) const
{
	//TRUEで終了時最初の位置に戻る
	alSourcei(id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}
bool CSource::IsPlay() const
{
	//現在の状態を返す
	ALint state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
float CSource::GetTime() const
{
	//現在の再生時間を返す
	ALfloat nowtime;
	alGetSourcef(id, AL_SEC_OFFSET, &nowtime);
	return nowtime;
}
void CSource::SetTime(const float time) const
{
	alSourcef(id, AL_SEC_OFFSET, time);
}
void CSource::QueueBuffer(const CBuffer& buffer) const
{
	ALuint buffers = buffer.GetID();
	//バッファネームのキューを作成
	alSourceQueueBuffers(id, 1, &buffers);
}
ALuint CSource::UnqueueBuffer() const
{
	ALuint buffers;
	//キューからバッファを除去する
	alSourceUnqueueBuffers(id, 1, &buffers);
	return buffers;
}
int CSource::GetProcessed() const
{
	int pro_;
	//再生済みのバッファ数を返す
	alGetSourcei(id, AL_BUFFERS_PROCESSED, &pro_);
	return pro_;
}
int CSource::GetQueued() const
{
	int queued;
	alGetSourcei(id, AL_BUFFERS_QUEUED, &queued);
	return queued;
}
float CSource::GetPitch() const
{
	float pitch;
	alGetSourcef(id, AL_PITCH, &pitch);
	return pitch;
}
float CSource::GetVolume() const
{
	float volume;
	alGetSourcef(id, AL_GAIN, &volume);
	return volume;
}
int CSource::GetLoop() const
{
	int loop;
	alGetSourcei(id, AL_LOOPING, &loop);
	return loop;
}
int CSource::GetSourceType() const
{
	int type;
	alGetSourcei(id, AL_SOURCE_TYPE, &type);
	return type;
}
void CSource::SetReferenceDistance(const float distance) const
{
	alSourcef(id, AL_REFERENCE_DISTANCE, distance);
}
float CSource::GetReferenceDistance() const
{
	float distance;
	alGetSourcef(id, AL_REFERENCE_DISTANCE, &distance);
	return distance;
}
void CSource::SetRolloffFactor(const float factor) const
{
	alSourcef(id, AL_ROLLOFF_FACTOR, factor);
}
float CSource::GetRolloffFactor() const
{
	float factor;
	alGetSourcef(id, AL_ROLLOFF_FACTOR, &factor);
	return factor;
}
void CSource::SetPosition(const CVec3& position) const
{
	alSource3f(id, AL_POSITION, position.x, position.y, position.z);
}
CVec3 CSource::GetPosition() const
{
	CVec3 position;
	alGetSource3f(id, AL_POSITION, &position.x, &position.y, &position.z);
	return position;
}
void CSource::SetVelocity(const CVec3& velocity) const
{
	alSource3f(id, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
CVec3 CSource::GetVelocity() const
{
	CVec3 velocity;
	alGetSource3f(id, AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
void CSource::SetDirection(const CVec3& direction) const
{
	alSource3f(id, AL_DIRECTION, direction.x, direction.y, direction.z);
}
CVec3 CSource::GetDirection() const
{
	CVec3 direction;
	alGetSource3f(id, AL_DIRECTION, &direction.x, &direction.y, &direction.z);
	return direction;
}
void CSource::SetConeInnerAngle(const float angle) const
{
	alSourcef(id, AL_CONE_INNER_ANGLE, angle);
}
float CSource::GetConeInnerAngle() const
{
	float angle;
	alGetSourcef(id, AL_CONE_INNER_ANGLE, &angle);
	return angle;
}
void CSource::SetConeOuterAngle(const float angle) const
{
	alSourcef(id, AL_CONE_OUTER_ANGLE, angle);
}
float CSource::GetConeOuterAngle() const
{
	float angle;
	alGetSourcef(id, AL_CONE_OUTER_ANGLE, &angle);
	return angle;
}
void CSource::SetConeOuterGain(const float volume) const
{
	alSourcef(id, AL_CONE_OUTER_GAIN, volume);
}
float CSource::GetConeOuterGain() const
{
	float gain;
	alGetSourcef(id, AL_CONE_OUTER_GAIN, &gain);
	return gain;
}
void CSource::SetOrientation(const float* orientation)
{
	alListenerfv(AL_ORIENTATION, orientation);
}
float* CSource::GetOrientation(float* orientation)
{
	alGetListenerfv(AL_ORIENTATION, orientation);
	return orientation;	
}
void CSource::SetListenerPosition(const CVec3& position)
{
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}
CVec3 CSource::GetListenerPosition()
{
	CVec3 position;
	alGetListener3f(AL_POSITION, &position.x, &position.y, &position.z);
	return position;
}
void CSource::SetListenerVelocity(const CVec3& velocity)
{
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}
CVec3 CSource::GetListenerVelocity()
{
	CVec3 velocity;
	alGetListener3f(AL_VELOCITY, &velocity.x, &velocity.y, &velocity.z);
	return velocity;
}
void CSource::SetListenerGain(const float volume)
{
	alListenerf(AL_GAIN, volume);
}
float CSource::GetListenerGain()
{
	float volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}
//---------------------------------
//@:Wavclass
//---------------------------------
CWav::CWav(const std::string& file)
{
	std::ifstream fstr(file, std::ios::binary);
	if (!fstr)
	{
#if DEBUG_ENABLE
		std::cout << "ファイル読み込みエラー" << std::endl;
#endif
		throw;
	}
	// ファイル情報を解析
	if (!CWav::analyzeWavFile(info, fstr))
	{
#if DEBUG_ENABLE
		std::cout << "Wavファイル読み込みエラー: " << file << std::endl;
#endif		
		throw;
	}
	if ((info.id != 1) || (info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
#if DEBUG_ENABLE
		std::cout << "Wavファイルのフォーマットエラー" << std::endl;
#endif
		throw;
	}
	// 再生時間(秒)
	time_ = info.size / info.ch / 2.0f / info.sample_rate;
	// データ読み込み
	data_.resize(info.size);
	CWav::searchChunk(fstr, "data");
	fstr.seekg(4, fstr.cur);
	fstr.read(&data_[0], info.size);
}
u_int CWav::channel() const
{
	return info.ch;
}
bool CWav::isStereo() const
{
	return info.ch == 2;
}
u_int CWav::sampleRate() const
{
	return info.sample_rate;
}
u_int CWav::size() const
{
	return info.size;
}
float CWav::time() const
{
	return time_;
}
const char* CWav::data() const
{
	return &data_[0];
}
const char* CWav::data(const size_t& number) const
{
	return &data_[number];
}
u_int CWav::getValue(const char* ptr, const u_int num)
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
bool CWav::searchChunk(std::ifstream& fstr, const char* chunk)
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
		u_int chunk_size = CWav::getValue(data, 4);
		fstr.seekg(chunk_size, fstr.cur);
		if (fstr.eof())
		{
			break;
		}
	}
	return false;
}
u_int CWav::getChunkSize(std::ifstream& fstr)
{
	char data[4];
	fstr.read(data, 4);
	return CWav::getValue(data, 4);
}
bool CWav::analyzeWavFile(Info& info, std::ifstream& fstr)
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
#if DEBUG_ENABLE
		std::cout << "このファイルはRIFFではありません" << std::endl;
#endif
		return false;
	}
	if (std::strncmp(&header[8], "WAVE", 4))
	{
#if DEBUG_ENABLE
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
#if DEBUG_ENABLE
		std::cout << "fmtチャンクが存在しません" << std::endl;
#endif
		return false;
	}
	u_int chunk_size = CWav::getChunkSize(fstr);
	std::vector<char> chunk(chunk_size);
	fstr.read(&chunk[0], chunk_size);
	info.id = CWav::getValue(&chunk[WAV_ID], 2);
	info.ch = CWav::getValue(&chunk[WAV_CH], 2);
	info.sample_rate = CWav::getValue(&chunk[WAV_SAMPLE_RATE], 4);
	info.bit = CWav::getValue(&chunk[WAV_BIT], 2);
	// dataチャンクを探してデータ長を取得
	if (!searchChunk(fstr, "data"))
	{
#if DEBUG_ENABLE
		std::cout << "dataチャンクが存在しません" << std::endl;
#endif
		return false;
	}
	info.size = CWav::getChunkSize(fstr);
	return true;
}
std::vector<char> CWav::Getdata()
{
	return data_;
}
void CWav::TestFunction(const float value)
{
	for (auto it : data_)
	{
		it *= value;
	}
}
//---------------------------------
//@:StreamWavclass
//---------------------------------
CStreamWav::CStreamWav(const std::string& file) :
	fstr_(file, std::ios::binary),
	loop_(false)
{
	if (!fstr_) throw "ファイルを開くことができません";
	// ファイル情報を解析
	if (!CWav::analyzeWavFile(info, fstr_))
	{
		return;
	}
	if ((info.id != 1) || (info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
#if DEBUG_ENABLE
		std::cout << "Wavファイルフォーマットエラー" << std::endl;
#endif
		return;
	}
	last_size_ = info.size;
	// データの先頭位置を覚えておく
	top_pos_ = static_cast<size_t>(fstr_.tellg());
}
bool CStreamWav::isStereo() const
{
	return info.ch == 2;
}
u_int CStreamWav::sampleRate() const
{
	return info.sample_rate;
}
size_t CStreamWav::GetlastSize() const
{
	return last_size_;
}
void CStreamWav::loop(const bool loop)
{
	loop_ = loop;
}
void CStreamWav::toTop()
{
	fstr_.seekg(top_pos_, fstr_.beg);
	last_size_ = info.size;
}
bool CStreamWav::isEnd() const
{
	return last_size_ == 0;
}
size_t CStreamWav::read(std::vector<char>& buffer)
{
	size_t remain_size = buffer.size();
	// ループしない場合、残りの中途半端なサイズを読み込んで終了
	if (!loop_ && (last_size_ < remain_size))
	{
		remain_size = last_size_;
	}
	size_t offset = 0;
	size_t total_read_size = 0;
	// ループ再生の場合はバッファを満たすまでデータを読み込む
	while (remain_size > 0) {
		size_t read_size = CStreamWav::readData(buffer, offset, remain_size);

		total_read_size += read_size;
		remain_size -= read_size;
		last_size_ -= read_size;
		offset += read_size;
		if (loop_ && !last_size_)
		{
			CStreamWav::toTop();
		}
	}
	return total_read_size;
}
size_t CStreamWav::readData(std::vector<char>& buffer, const size_t offset, const size_t size)
{
	size_t read_size = (size < last_size_) ? size : last_size_;
	fstr_.read(&buffer[offset], read_size);
	return read_size;
}