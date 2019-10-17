#pragma once
#include "Engine\EngineMacro.h"
#include "NonCopyable\NonCopyable.hpp"
#include <vector>
#include <string>

#if WINDOWS_BUILD
class CWindowsEvent : private CNonCopyable
{
	std::vector<std::string>* loadPath;
	std::vector<std::string>* notLoadFileName;
	void FileLoad(const std::string& filepath, std::vector<std::string>* vec);
public:
	explicit CWindowsEvent();
	virtual ~CWindowsEvent();
	std::vector<std::string> ResourceFileNameLoad(const std::string& filepath);
	void SetLoadPath(const std::string& path);
	void SetNotLoadFileName(const std::string& name);
};
#endif // WINDOWS_BUILD