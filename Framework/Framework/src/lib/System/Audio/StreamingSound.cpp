#include "StreamingSound.h"
//---------------------------------
//@:StrimingSoundclass
//---------------------------------
void StreamingSound::queueStream(StreamWav& stream, Source& source, Buffer& buffer, std::vector<char>& sound_buffer)
{
	size_t length = stream.read(sound_buffer);
	buffer.Bind(stream.isStereo(), &sound_buffer[0], static_cast<u_int>(length), stream.sampleRate());
	source.QueueBuffer(buffer);
}
void StreamingSound::streamProc(const std::string& path, const bool loop, std::shared_ptr<Source>& source, std::shared_ptr<Param>& param)
{
	StreamWav stream(path);
	stream.loop(loop);
	Buffer buffer[BUFFER_NUM];
	// �ǂݍ��݃o�b�t�@��1�b�Ԃ�̒����ɂ���
	u_int buffer_size = stream.sampleRate() * (stream.isStereo() ? 2 : 1) * sizeof(uint16_t);
	std::vector<char> sound_buffer(buffer_size);
	// ���ׂẴX�g���[���o�b�t�@���Đ��L���[�ɐς�
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
					// �Đ��̏I������o�b�t�@���ăL���[�C���O
					queueStream(stream, *source, buffer[i], sound_buffer);
					break;
				}
			}
		}
		//�w�肵�����Ԃ����X���b�h���u���b�N����
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MS));
	}
#ifdef KL_DEBUG
	std::cout << "Streaming�I��" << std::endl;
#endif 
	//stream.End();
}
StreamingSound::StreamingSound()
{

}
StreamingSound::StreamingSound(const std::string& path, const bool loop) :
	source_(std::make_shared<Source>()),
	param_(std::make_shared<Param>()),
	pause_(false)
{
	filepath_ = path;
	loop_ = loop;
	isplay_ = false;
	param_->backStartPos = false;
}
void StreamingSound::createSound(const std::string& path_, bool loop)
{
	source_ = std::make_shared<Source>();
	param_ = std::make_shared<Param>();
	pause_ = false;
	filepath_ = path_;
	loop_ = loop;
	isplay_ = false;
	param_->backStartPos = false;
}
void StreamingSound::gain(const float gain)
{
	source_->SetVolume(gain);
}
void StreamingSound::pitch(const float value_) const
{
	source_->SetPitch(value_);
}
void StreamingSound::pause()
{
	//�ʃX���b�h�����b�N����
	param_->mutex.lock();
	bool stopped = param_->stopped;
	//�ʃX���b�h�̃��b�N����������
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
void StreamingSound::stop()
{
	param_->mutex.lock();
	source_->Stop();
	param_->mutex.unlock();
	isplay_ = false;
}
bool StreamingSound::isPlaying()
{
	param_->mutex.lock();
	bool stopped = param_->stopped;
	param_->mutex.unlock();
	if (stopped) return false;
	return source_->IsPlay();
}
void StreamingSound::play()
{
	if (!isplay_) {
	//���s�X���b�h�̐���
	std::thread thread(streamProc, filepath_, loop_, std::ref(source_), std::ref(param_));
	//�X���b�h�̊Ǘ��������
	thread.detach();
	param_->mutex.lock();
	param_->stopped = false;
	param_->mutex.unlock();
	isplay_ = true;
	}
}
void StreamingSound::DeleteSound()
{
	gain(0.0);
	//�X���b�h�Ԃ̏������擾����
	std::lock_guard<std::mutex>(param_->mutex);
	param_->stopped = true;
	isplay_ = false;
}
float StreamingSound::GetTime() const
{
	//���݂̎��Ԃ�Ԃ�����streaming������1�b���Ƃɓǂݍ��ݒ�������0~1���炢�����Ԃ�Ȃ���
	return source_->GetTime();
}
#ifdef KL_DEBUG
void StreamingSound::debugUpdata()
{

}
#endif