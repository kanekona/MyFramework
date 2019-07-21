#include "WindowsEvent.h"
#include "System\System.h"
WindowsEvent::WindowsEvent()
{
	loadPath = nullptr;
	notLoadFileName = nullptr;
}
WindowsEvent::~WindowsEvent()
{
	if (loadPath)
	{
		delete loadPath;
	}
	if (notLoadFileName)
	{
		delete notLoadFileName;
	}
}
void WindowsEvent::SetLoadPath(const std::string& path)
{
	if (loadPath)
	{
		loadPath->emplace_back(path);
	}
	else
	{
		loadPath = new std::vector<std::string>;
		loadPath->emplace_back(path);
	}
}
void WindowsEvent::SetNotLoadFileName(const std::string& name)
{
	if (notLoadFileName)
	{
		notLoadFileName->emplace_back(name);
	}
	else
	{
		notLoadFileName = new std::vector<std::string>;
		notLoadFileName->emplace_back(name);
	}
}

std::vector<std::string> WindowsEvent::ResourceFileNameLoad(const std::string& filepath)
{
	std::vector<std::string> filename;
	FileLoad(filepath, &filename);
	return filename;
}


void WindowsEvent::FileLoad(const std::string& filepath, std::vector<std::string>* vec)
{
	WIN32_FIND_DATA findData;
	std::string allFilePath =  filepath + "\\*.*";
	HANDLE hfile = FindFirstFile(allFilePath.c_str(), &findData);
	if (INVALID_HANDLE_VALUE == hfile)
	{
		return;
	}
	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if ('.' == findData.cFileName[0])
			{
				if (('\0' == findData.cFileName[1]) || ('.' == findData.cFileName[1] && '\0' == findData.cFileName[2]))
				{
					continue;
				}
			}
			if (notLoadFileName)
			{
				std::string tmp = findData.cFileName;
				for (int i = 0; i < notLoadFileName->size(); ++i)
				{
					std::cout << findData.cFileName << ":" << *notLoadFileName[i].data() << "\n";
					//if (!OG::CheckText(&tmp, &(*notLoadFileName)[i]))
					if(tmp != notLoadFileName->at(i))
					{
						FileLoad(allFilePath.substr(0, allFilePath.size() - 4) + "\\" + findData.cFileName, vec);
						break;
					}
				}
			}
			else
			{
				FileLoad(allFilePath.substr(0, allFilePath.size() - 4) + "\\" + findData.cFileName, vec);
			}
		}
		else
		{
			if (loadPath)
			{
				std::string tmp = findData.cFileName;
				for (int i = 0; i < loadPath->size(); ++i)
				{
					if (KL::CheckText(&tmp, &(*loadPath)[i]))
					{
						vec->emplace_back(std::string(allFilePath.substr(0, allFilePath.size() - 4) + "\\" + findData.cFileName));
						break;
					}
				}
			}
			else
			{
				vec->emplace_back(std::string(allFilePath.substr(0, allFilePath.size() - 4) + "\\" + findData.cFileName));
			}
		}
	} while (FindNextFile(hfile, &findData));
	FindClose(hfile);
}