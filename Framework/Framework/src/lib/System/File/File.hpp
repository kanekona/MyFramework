#pragma once
#include <sstream>
#include <fstream>
#include <string>
typedef int FileFormat;
class File final
{
public:
	static const FileFormat KL_MALLOC;
	static const FileFormat KL_NEW;
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
		return File::Load(ifs);
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
	static unsigned int Count(const std::string& str, const char c)
	{
		return std::count(str.cbegin(), str.cend(), c);
	}
	// One line String Attay
	static std::string* Load(const std::string& path, const unsigned int count, const FileFormat config)
	{
		std::ifstream ifs(path, std::ios::in);
		if (!ifs)
		{
			return nullptr;
		}
		std::string* texts = nullptr;
		switch (config)
		{
		case 0x00:
			texts = (std::string*)malloc(count);
			break;
		case 0x01:
			texts = new std::string[count];
			break;
		default:
			return nullptr;
			break;
		}
		static std::string line;
		unsigned int i = 0;
		while (std::getline(ifs, line))
		{
			texts[i] = line;
			++i;
		}
		return texts;
	}
};