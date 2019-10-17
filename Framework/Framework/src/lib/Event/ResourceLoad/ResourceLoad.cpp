#include "ResourceLoad.h"
#include "ResourceManager\ResourceManager.h"
CResourceLoad::CResourceLoad(std::ifstream& ifs)
{
	std::string lineText;
	while (std::getline(ifs, lineText))
	{
		//'/'が頭についているものは読み込まない
		if (lineText.at(0) == '/')
		{
			continue;
		}
		DataCreate(lineText);
	}
}
CResourceLoad::~CResourceLoad()
{

}
void CResourceLoad::DataCreate(const std::string& text)
{
	//'>'の前と後でstringデータをわける
	std::string::size_type t = text.find(">");
	dataPath = text.substr(0, t);
	dataName = text.substr(t + 1);
	//文字列の中に以下の文字が含まれていればその部分を空白へ変更する
	while ((t = dataName.find_first_of("(,);")) != std::string::npos)
	{
		dataName[t] = ' ';
	}
	std::stringstream ss;
	ss << dataName;

	std::string path, name;

	if (dataPath == "Texture")
	{
		ss >> path >> name;
		CResourceManager::Get()->CreateTexture(name, path);
	}
	else if (dataPath == "Sound")
	{
		ss >> path >> name;
		CResourceManager::Get()->CreateSound(name, path);
	}
	else if (dataPath == "Shader")
	{
		ss >> path >> name;
		CResourceManager::Get()->CreateShader(name, path);
	}
	else
	{
#if DEBUG_ENABLE
		std::cout << "ResourceLoad>>未登録の形式です\n";
#endif
	}
}