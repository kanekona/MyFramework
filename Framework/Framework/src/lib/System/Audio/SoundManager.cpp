#include "SoundManager.h"
CSoundManager::CSoundManager()
{
	MaxVolume = 1.0f;
}
void CSoundManager::SetMaxVolume(const float volume_)
{
	MaxVolume = volume_;
}
float CSoundManager::GetMaxVolume() const
{
	return MaxVolume;
}
void CSoundManager::SetVolume(const CSound* s, const float value_)
{
	s->Volume(value_ * MaxVolume);
}
void CSoundManager::SetSound(CSound* s) 
{
	sounddata.emplace_back(s);
}
bool CSoundManager::DeleteSound(const CSound* s) 
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
void CSoundManager::AllDelete() 
{
	sounddata.clear();
}
CSoundManager::~CSoundManager()
{
	sounddata.clear();
}
void CSoundManager::Application()
{
	for (unsigned int i = 0; i < sounddata.size(); ++i)
	{
		sounddata[i]->Volume(sounddata[i]->GetVolume() * GetMaxVolume());
	}
}