#include "Sound.h"
//---------------------------------
//@:Soundclass
//---------------------------------
Sound::Sound()
{

};
Sound::Sound(const std::string& path_, const bool loop) :
	buffer(std::make_shared<Buffer>(path_)),
	source(std::make_shared<Source>()),
	path(path_)
{
	this->source->BindBuffer(*this->buffer);
	this->Looping(loop);
	this->Pitch(1.0f);
	this->volume_ = 1.0f;
	this->Volume(this->volume_);
	this->oneSecondWaveformData = buffer->sampleRate;
	this->allWaveformData = (unsigned int)buffer->waveformData.size();
}
Sound::~Sound()
{

};
bool Sound::Create(const std::string& path_, const bool loop)
{
	this->buffer = std::make_shared<Buffer>(path_);
	this->source = std::make_shared<Source>();
	path = path_;
	this->source->BindBuffer(*this->buffer);
	this->Looping(loop);
	this->Pitch(1.0f);
	this->volume_ = 1.0f;
	this->Volume(this->volume_);
	this->oneSecondWaveformData = buffer->sampleRate;
	this->allWaveformData = (unsigned int)buffer->waveformData.size();
	return true;
}
void Sound::Play() const
{
	this->source->Play();
}
void Sound::Stop() const
{
	this->source->Stop();
}
void Sound::Pause() const
{
	this->source->Pause();
}
void Sound::Volume(const float value_) const
{
	this->source->SetVolume(value_);
}
void Sound::Pitch(const float value_) const
{
	this->source->SetPitch(value_);
}
void Sound::Looping(const bool loop_) const
{
	this->source->SetLoop(loop_);
}
bool Sound::IsPlay() const
{
	return source && source->IsPlay();
}
float Sound::CurrentTime() const
{
	return this->source->GetTime();
}
float Sound::Duration() const
{
	return this->buffer->GetTime();
}
void Sound::SetVolume(float maxVolume_)
{
	this->volume_ = maxVolume_;
}
float Sound::GetVolume() const
{
	return this->volume_;
}
Buffer* Sound::GetBuffer() const
{
	return &*buffer;
}
void Sound::Skip(const float time)
{
	source->SetTime(time);
}