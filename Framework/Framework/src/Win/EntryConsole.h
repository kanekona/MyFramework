#pragma once
#ifdef CONSOLE_BUILD
#include "System\Console\ConsoleSystem.h"
class CEntryConsole : public CConsoleBase
{
	virtual void Entry() override;
	virtual void Update() override;
};
#endif