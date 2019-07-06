#include "System\System.h"
#include "Engine\Engine.h"
#include "StrID\StrID.h"
//メモリリーク検知
#if (DEBUG_ENABLE)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
/**
*@brief	エントリーポイント
*/
int main() {
	//メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	StrIDSystem::Create();
	//Declaration Engine
	Engine* engine = nullptr;
	try
	{
		//Create Engine
		engine = new Engine();
	}
	catch (int errorcode)
	{
		//Error Check
#if DEBUG_ENABLE
		std::cout << errorcode << std::endl;
#endif
		delete engine;
		return errorcode;
	}
	//Main Loop
	while (engine->SystemUpdate())
	{

	}
	//Delete Engine
	delete engine;
	StrIDSystem::Delete();
}