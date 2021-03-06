#include "StreamingSound.h"
//---------------------------------
//@:StrimingSoundclass
//---------------------------------
void CStreamingSound::queueStream(CStreamWav& stream, CSource& source, CBuffer& buffer, std::vector<char>& sound_buffer)
{
	size_t length = stream.read(sound_buffer);
	buffer.Bind(stream.isStereo(), &sound_buffer[0], static_cast<u_int>(length), stream.sampleRate());
	source.QueueBuffer(buffer);
}
void CStreamingSound::streamProc(const std::string& path, const bool loop, std::shared_ptr<CSource>& source, std::shared_ptr<Param>& param)
{
	CStreamWav stream(path);
	stream.loop(loop);
	CBuffer buffer[BUFFER_NUM];
	// 読み込みバッファを1秒ぶんの長さにする
	u_int buffer_size = stream.sampleRate() * (stream.isStereo() ? 2 : 1) * sizeof(uint16_t);
	std::vector<char> sound_buffer(buffer_size);
	// すべてのストリームバッファを再生キューに積む
	for (u_int i = 0; i < BUFFER_NUM; ++i)
	{
		queueStream(stream, *source, buffer[i], sound_buffer);
	}
	source->SetVolume(1.0);
	source->Play();
	while (!stream.isEnd())
	{
		//std::cout << stream.GetlastSize() << std::endl;
		param->mutex.lock();
		bool stopped = param->stopped;
		param->backStartPos = false;
		param->mutex.unlock();
		if (stopped) { break; }
	//	stream.BackSound = back;
		if (source->GetProcessed() > 0)
		{
			ALuint buffer_id = source->UnqueueBuffer();
			for (u_int i = 0; i < BUFFER_NUM; ++i)
			{
				if (buffer_id == buffer[i].GetID())
				{
					// 再生の終わったバッファを再キューイング
					queueStream(stream, *source, buffer[i], sound_buffer);
					break;
				}
			}
		}
		//指定した時間だけスレッドをブロックする
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));
	}
#ifdef KL_DEBUG
	std::cout << "Streaming終了" << std::endl;
#endif 
	//stream.End();
}
CStreamingSound::CStreamingSound()
{

}
CStreamingSound::CStreamingSound(const std::string& path, const bool loop) :
	source_(std::make_shared<CSource>()),
	param_(std::make_shared<Param>()),
	pause_(false)
{
	filepath_ = path;
	loop_ = loop;
	isplay_ = false;
	param_->backStartPos = false;
}
void CStreamingSound::createSound(const std::string& path_, bool loop)
{
	source_ = std::make_shared<CSource>();
	param_ = std::make_shared<Param>();
	pause_ = false;
	filepath_ = path_;
	loop_ = loop;
	isplay_ = false;
	param_->backStartPos = false;
}
void CStreamingSound::gain(const float gain)
{
	source_->SetVolume(gain);
}
void CStreamingSound::pitch(const float value_) const
{
	source_->SetPitch(value_);
}
void CStreamingSound::pause()
{
	//別スレッドをロックする
	param_->mutex.lock();
	bool stopped = param_->stopped;
	//別スレッドのロックを解除する
	param_->mutex.unlock();
	if (stopped) return;
	if (isplay_)
	{
		source_->Pause();
		isplay_ = false;
	}
	else
	{
		source_->Play();
		isplay_ = true;
	}
}
void CStreamingSound::stop()
{
	param_->mutex.lock();
	source_->Stop();
	param_->mutex.unlock();
	isplay_ = false;
}
bool CStreamingSound::isPlaying()
{
	param_->mutex.lock();
	bool stopped = param_->stopped;
	param_->mutex.unlock();
	if (stopped) return false;
	return source_->IsPlay();
}
void CStreamingSound::play()
{
	if (!isplay_) {
	//実行スレッドの生成
	std::thread thread(streamProc, filepath_, loop_, std::ref(source_), std::ref(param_));
	//スレッドの管理を手放す
	thread.detach();
	param_->mutex.lock();
	param_->stopped = false;
	param_->mutex.unlock();
	isplay_ = true;
	}
}
void CStreamingSound::DeleteSound()
{
	gain(0.0);
	//スレッド間の処理を取得する
	std::lock_guard<std::mutex>(param_->mutex);
	param_->stopped = true;
	isplay_ = false;
}
float CStreamingSound::GetTime() const
{
	//現在の時間を返すけどstreamingだから1秒ごとに読み込み直すから0~1くらいしか返らないよ
	return source_->GetTime();
}
#ifdef KL_DEBUG
void CStreamingSound::debugUpdata()
{

}
#endif