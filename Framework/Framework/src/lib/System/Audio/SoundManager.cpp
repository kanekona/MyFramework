#include "SoundManager.h"
SoundManager::SoundManager()
{
	MaxVolume = 1.0f;
}
void SoundManager::SetMaxVolume(const float volume_)
{
	MaxVolume = volume_;
}
float SoundManager::GetMaxVolume() const
{
	return MaxVolume;
}
void SoundManager::SetVolume(const Sound* s, const float value_)
{
	s->Volume(value_ * MaxVolume);
}
void SoundManager::SetSound(Sound* s) 
{
	sounddata.emplace_back(s);
}
bool SoundManager::DeleteSound(const Sound* s) 
{
	for (auto id = sounddata.begin(); id != sounddata.end(); ++id)
	{
		if ((*id) == s)
		{
			sounddata.erase(id);
			return true;
		}
	}
	return false;
}
void SoundManager::AllDelete() 
{
	sounddata.clear();
}
SoundManager::~SoundManager()
{
	sounddata.clear();
}
void SoundManager::Application()
{
	for (unsigned int i = 0; i < sounddata.size(); ++i)
	{
		sounddata[i]->Volume(sounddata[i]->GetVolume() * GetMaxVolume());
	}
}