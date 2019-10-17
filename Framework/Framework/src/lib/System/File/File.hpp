#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "System\System.h"
#include "Engine\EngineTypedef.h"
typedef uint8 TFileFormat;
class CFile final
{
public:
	static const TFileFormat KL_MALLOC = 0x00;
	static const TFileFormat KL_NEW = 0x01;
	// Reading files
	static std::string Load(std::ifstream& ifs)
	{
		std::istreambuf_iterator<char> begin(ifs);
		std::istreambuf_iterator<char> end;
		return std::string(begin, end);
	}
	// Reading files
	static std::string Load(const std::string& path)
	{
		std::ifstream ifs(path, std::ios::in | std::ios::binary);
		return CFile::Load(ifs);
	}
	// File Output
	static void Output(const std::string& path, const std::string& text)
	{
		std::ofstream ofs(path, std::ios::out, std::ios::binary);
		ofs << text;
		ofs.close();
	}
	// File Append Output
	static void AddOutput(const std::string& path, const std::string& text)
	{
		std::ofstream ofs(path, std::ios::app, std::ios::binary);
		ofs << text;
		ofs.close();
	}
	// Delete the contents of the file
	static void DeleteContents(const std::string& path)
	{
		std::ofstream ofs(path, std::ios::trunc);
		ofs.close();
	}
	// Create file
	static void Create(const std::string& path)
	{
		std::ofstream ofs(path);
		ofs.close();
	}
	// Get the data of the specified tag
	static std::string GetData(const std::string& path, const std::string& tag)
	{
		std::ifstream ifs(path);
		std::string line;
		while (std::getline(ifs, line))
		{
			if (line.at(0) == '/')
			{
				continue;
			}
			if (tag == line.substr(0, line.find_first_of("=")))
			{
				return line.substr(line.find_first_of("=") + 1);
			}
		}
		return std::string();
	}
	// Get the data of the specified tag
	static std::string GetData(const std::string& path, const unsigned int tag)
	{
		std::ostringstream oss;
		oss << tag;
		std::ifstream ifs(path);
		std::string line;
		while (std::getline(ifs, line))
		{
			if (line.at(0) == '/')
			{
				continue;
			}
			if (oss.str() == line.substr(0, line.find("=")))
			{
				return line.substr(line.find("=") + 1);
			}
		}
		return std::string();
	}
	// Specified character count
	
	static unsigned int Count(const std::string& path)
	{
		std::string str = CFile::Load(path);
		return KL::Count(str, '\n');
	}
	// One line String Attay
	static std::string* LoadStrings(const std::string& path, const unsigned int count, const TFileFormat config = KL_NEW)
	{
		std::ifstream ifs(path, std::ios::in);
		if (!ifs)
		{
			return nullptr;
		}
		std::string* texts = nullptr;
		switch (config)
		{
		case CFile::KL_MALLOC:
			texts = (std::string*)malloc(count);
			break;
		case CFile::KL_NEW:
			texts = new std::string[count];
			break;
		default:
			return nullptr;
			break;
		}
		std::string line;
		unsigned int i = 0;
		while (std::getline(ifs, line))
		{
			texts[i] = line;
			++i;
		}
		return texts;
	}
	static std::string* LoadStrings(const std::string& path, const TFileFormat config = KL_NEW)
	{
		return LoadStrings(path, Count(path) + 1, config);
	}
	static std::string* LoadStrings(const std::string& path, unsigned int * out, const TFileFormat config = KL_NEW)
	{
		*out = Count(path) + 1;
		return LoadStrings(path, *out, config);
	}
	static void LoadStrings(std::vector<std::string>* out, const std::string& path)
	{
		std::ifstream ifs(path, std::ios::in);
		std::string line;
		out->clear();
		while (std::getline(ifs, line))
		{
			out->emplace_back(line);
		}
	}
};