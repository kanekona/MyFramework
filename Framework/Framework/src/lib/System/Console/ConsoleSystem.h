#pragma once

#ifdef CONSOLE_BUILD
#include "NonCopyable\NonCopyable.hpp"
#include "Framerate\Framerate.h"

class CConsoleBase
{
public:
	virtual void Entry();
	virtual void Update();
};

class CConsoleSystem : private CNonCopyable
{
	CConsoleBase* console;
	CFramerate fps;
	bool isDelete;
	static CConsoleSystem* instance;
	explicit CConsoleSystem(CConsoleBase* startConsole);
	virtual ~CConsoleSystem();
public:
	static void Create();
	static CConsoleSystem* Get();
	static void Delete();
	bool Update();
	static void DeleteSystem();
};
#endif