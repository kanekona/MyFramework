#include "ResourceManager.h"

#include "Audio\Sound.h"
#include "Texture\Texture.h"
#include "Shader\Shader.h"

void CResourceManager::SetSoundData(const std::string& dataname,CSound* sound)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, CSound*> d;
	d.first = dataname;
	d.second = sound;
	soundData.emplace_back(d);
}

bool CResourceManager::CreateSound(const std::string& name,const std::string& path)
{
	for (auto id = soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	CSound* so = new CSound();
	so->Create(path);
	std::pair<std::string, CSound*> d;
	d.first = name;
	d.second = so;
	soundData.emplace_back(d);
	return true;
}

void CResourceManager::SetTextureData(const std::string& dataname, CTexture* texture)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, CTexture*> d;
	d.first = dataname;
	d.second = texture;
	textureData.emplace_back(d);
}

bool CResourceManager::CreateTexture(const std::string& name, const std::string& path)
{
	for (auto id = textureData.begin(); id != textureData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	CTexture* tex = new CTexture(path);
	std::pair<std::string, CTexture*> d;
	d.first = name;
	d.second = tex;
	textureData.emplace_back(d);
	return true;
}

CSound* CResourceManager::GetSoundData(const std::string& dataname)
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

CTexture* CResourceManager::GetTextureData(const std::string& dataname)
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

CResourceManager::~CResourceManager()
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

bool CResourceManager::DeleteTexture(const std::string& name)
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

bool CResourceManager::DeleteSound(const std::string& name)
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

bool CResourceManager::CreateShader(const std::string& name, const std::string& path)
{
	for (auto id = shaderData.begin(); id != shaderData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	CShader* shader = new CShader();
	shader->Read(path);
	shader->Use();
	std::pair<std::string, CShader*> d;
	d.first = name;
	d.second = shader;
	shaderData.emplace_back(d);
	return true;
}

CShader* CResourceManager::GetShaderData(const std::string& dataname)
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

CResourceManager* CResourceManager::Create()
{
	if (instance == nullptr)
	{
		instance = new CResourceManager();
	}
	return CResourceManager::Get();
}
CResourceManager* CResourceManager::Get()
{
	return instance;
}
void CResourceManager::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
CResourceManager* CResourceManager::instance = nullptr;