#include "Sound.h"
//---------------------------------
//@:Sound class
//---------------------------------
CSound::CSound()
{

};
CSound::CSound(const std::string& path_, const bool loop) :
	buffer(std::make_shared<CBuffer>(path_)),
	source(std::make_shared<CSource>()),
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
CSound::~CSound()
{

};
bool CSound::Create(const std::string& path_, const bool loop)
{
	buffer = std::make_shared<CBuffer>(path_);
	source = std::make_shared<CSource>();
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
void CSound::Play() const
{
	source->Play();
}
void CSound::Stop() const
{
	source->Stop();
}
void CSound::Pause() const
{
	source->Pause();
}
void CSound::Volume(const float value_) const
{
	source->SetVolume(value_);
}
void CSound::Pitch(const float value_) const
{
	source->SetPitch(value_);
}
void CSound::Looping(const bool loop_) const
{
	source->SetLoop(loop_);
}
bool CSound::IsPlay() const
{
	return source && source->IsPlay();
}
float CSound::CurrentTime() const
{
	return source->GetTime();
}
float CSound::Duration() const
{
	return buffer->GetTime();
}
void CSound::SetVolume(float maxVolume_)
{
	volume_ = maxVolume_;
}
float CSound::GetVolume() const
{
	return volume_;
}
CBuffer* CSound::GetBuffer() const
{
	return &*buffer;
}
CSource* CSound::GetSource() const
{
	return &*source;
}
void CSound::Skip(const float time)
{
	source->SetTime(time);
}
#if ENGINE_DEBUG
void CSound::Test()
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