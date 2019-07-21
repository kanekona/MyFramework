#include "Sound.h"
//---------------------------------
//@:Sound class
//---------------------------------
Sound::Sound()
{

};
Sound::Sound(const std::string& path_, const bool loop) :
	buffer(std::make_shared<Buffer>(path_)),
	source(std::make_shared<Source>()),
	path(path_)
{
	source->BindBuffer(*buffer);
	Looping(loop);
	Pitch(1.0f);
	volume_ = 1.0f;
	Volume(volume_);
	oneSecondWaveformData = buffer->sampleRate;
	allWaveformData = (unsigned int)buffer->waveformData.size();
}
Sound::~Sound()
{

};
bool Sound::Create(const std::string& path_, const bool loop)
{
	buffer = std::make_shared<Buffer>(path_);
	source = std::make_shared<Source>();
	path = path_;
	source->BindBuffer(*buffer);
	Looping(loop);
	Pitch(1.0f);
	volume_ = 1.0f;
	Volume(volume_);
	oneSecondWaveformData = buffer->sampleRate;
	allWaveformData = (unsigned int)buffer->waveformData.size();
	return true;
}
void Sound::Play() const
{
	source->Play();
}
void Sound::Stop() const
{
	source->Stop();
}
void Sound::Pause() const
{
	source->Pause();
}
void Sound::Volume(const float value_) const
{
	source->SetVolume(value_);
}
void Sound::Pitch(const float value_) const
{
	source->SetPitch(value_);
}
void Sound::Looping(const bool loop_) const
{
	source->SetLoop(loop_);
}
bool Sound::IsPlay() const
{
	return source && source->IsPlay();
}
float Sound::CurrentTime() const
{
	return source->GetTime();
}
float Sound::Duration() const
{
	return buffer->GetTime();
}
void Sound::SetVolume(float maxVolume_)
{
	volume_ = maxVolume_;
}
float Sound::GetVolume() const
{
	return volume_;
}
Buffer* Sound::GetBuffer() const
{
	return &*buffer;
}
Source* Sound::GetSource() const
{
	return &*source;
}
void Sound::Skip(const float time)
{
	source->SetTime(time);
}
#if ENGINE_DEBUG
void Sound::Test()
{
	fftwf_complex* in;
	fftwf_complex* out;
	in = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) *buffer->waveformData.size());
	out = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * buffer->waveformData.size());
	fftwf_plan plan = fftwf_plan_dft_1d(static_cast<int>(buffer->waveformData.size()), in, out, FFTW_FORWARD/*FFTW_BACKWARD*/, FFTW_ESTIMATE);
	for (int i = 0; i < buffer->waveformData.size(); ++i)
	{
		in[i][0] = /*buffer->waveformData[i];*/static_cast<float>(buffer->waveformData[i]);
		in[i][1] = 0.0f;
	}
	fftwf_execute(plan);
	for (int i = 0; i < buffer->waveformData.size(); ++i)
	{
		printf("in[%.3f][%.3f]out[%.3f][%.3f][%.3f][%.3f][%.3f]\n", 
			in[i][0],
			in[i][1],
			out[i][0] * out[i][0] + out[i][1] * out[i][1],
			sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]),
			atan2(out[i][0], out[i][1]), out[i][0], out[i][1]
		);
	}
	fftwf_destroy_plan(plan);
	fftwf_free(in);
	fftwf_free(out);
}
#endif // ENGINE_DEBUG