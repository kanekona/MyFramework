
#ifdef CONSOLE_BUILD

#include "ConsoleSystem.h"
#include "Win\EntryConsole.h"

void CConsoleBase::Entry()
{

}

void CConsoleBase::Update()
{
}

CConsoleSystem::CConsoleSystem(CConsoleBase* startConsole)
	:console(startConsole)
	,isDelete(false)
{
	console->Entry();
}

CConsoleSystem::~CConsoleSystem()
{
	delete console;
}

void CConsoleSystem::Create()
{
	if (!instance)
	{
		instance = new CConsoleSystem(new CEntryConsole());
	}
}

CConsoleSystem* CConsoleSystem::Get()
{
	return instance;
}

void CConsoleSystem::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool CConsoleSystem::Update()
{
	if (fps.FrameCheck() && console)
	{
		console->Update();
	}
	return isDelete;
}

void CConsoleSystem::DeleteSystem()
{
	instance->isDelete = true;
}

CConsoleSystem* CConsoleSystem::instance = nullptr;
#endif