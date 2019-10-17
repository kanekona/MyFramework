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
#ifdef CONSOLE_BUILD
#include "Console\ConsoleSystem.h"
#endif
/**
*@brief	エントリーポイント
*/
int main() {
	//メモリリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CStrIDSystem::Create();
#ifdef CONSOLE_BUILD
	CConsoleSystem::Create();
	//OpenGL,OpenFW Initialize
	glfwInit();
	CConsoleSystem* CY = CConsoleSystem::Get();
	while (!CY->Update())
	{
	}
	CConsoleSystem::Delete();
	glfwTerminate();
	system("pause");
#else
	//Declaration Engine
	CEngine* engine = nullptr;
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
#endif
	CStrIDSystem::Delete();
}