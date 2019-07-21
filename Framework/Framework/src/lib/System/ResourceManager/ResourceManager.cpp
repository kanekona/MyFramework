#include "ResourceManager.h"

void ResourceManager::SetSoundData(const std::string& dataname,Sound* sound)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, Sound*> d;
	d.first = dataname;
	d.second = sound;
	soundData.emplace_back(d);
}

bool ResourceManager::CreateSound(const std::string& name,const std::string& path)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	Sound* so = new Sound();
	so->Create(path);
	std::pair<std::string, Sound*> d;
	d.first = name;
	d.second = so;
	soundData.emplace_back(d);
	return true;
}

void ResourceManager::SetTextureData(const std::string& dataname, Texture* texture)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, Texture*> d;
	d.first = dataname;
	d.second = texture;
	textureData.emplace_back(d);
}

bool ResourceManager::CreateTexture(const std::string& name, const std::string& path)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	Texture* tex = new Texture(path);
	std::pair<std::string, Texture*> d;
	d.first = name;
	d.second = tex;
	textureData.emplace_back(d);
	return true;
}

Sound* ResourceManager::GetSoundData(const std::string& dataname)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return (*id).second;
		}
	}
	return nullptr;
}

Texture* ResourceManager::GetTextureData(const std::string& dataname)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return (*id).second;
		}
	}
	return nullptr;
}

ResourceManager::~ResourceManager()
{
	for (auto& d : soundData)
	{
		if (d.second)
		{
			delete d.second;
		}
	}
	for (auto& d : textureData)
	{
		if (d.second)
		{
			delete d.second;
		}
	}
	for (auto& d : shaderData)
	{
		if (d.second)
		{
			delete d.second;
		}
	}
	soundData.clear();
	textureData.clear();
	shaderData.clear();
}

bool ResourceManager::DeleteTexture(const std::string& name)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == name)
		{
			if ((*id).second)
			{
				delete (*id).second;
			}
			textureData.erase(id);
			return true;
		}
	}
	return false;
}

bool ResourceManager::DeleteSound(const std::string& name)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == name)
		{
			if ((*id).second)
			{
				delete (*id).second;
			}
			soundData.erase(id);
			return true;
		}
	}
	return false;
}

bool ResourceManager::CreateShader(const std::string& name, const std::string& path)
{
	for (auto id = shaderData.begin(); id != shaderData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	Shader* shader = new Shader();
	shader->Read(path);
	shader->Use();
	std::pair<std::string, Shader*> d;
	d.first = name;
	d.second = shader;
	shaderData.emplace_back(d);
	return true;
}

Shader* ResourceManager::GetShaderData(const std::string& dataname)
{
	for (auto id = shaderData.begin(); id != shaderData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return (*id).second;
		}
	}
	return nullptr;
}

ResourceManager* ResourceManager::Create()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return ResourceManager::Get();
}
ResourceManager* ResourceManager::Get()
{
	return instance;
}
void ResourceManager::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
ResourceManager* ResourceManager::instance = nullptr;