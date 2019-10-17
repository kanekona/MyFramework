#ifdef CONSOLE_BUILD

#include "EntryConsole.h"
#include "Engine\EngineTypedef.h"
#include "Entity\EntityLayer.h"
#include "StrID\StrID.h"

void CEntryConsole::Entry()
{
	std::cout << sizeof(ELayer) << std::endl;
	std::cout << sizeof(uint8) << std::endl;
	std::cout << sizeof(uint8*) << std::endl;
	std::cout << sizeof(CMax::Int16) << std::endl;
	std::cout << sizeof(CStrID) << std::endl;
}

void CEntryConsole::Update()
{
	CConsoleSystem::Get()->DeleteSystem();
}

#endif
