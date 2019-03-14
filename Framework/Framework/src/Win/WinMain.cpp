#include "ResourceManager\ResourceManager.h"
#include "Input\Input.h"
#include "Engine\Engine.h"
#if !defined (_DEBUG)
// Degub版のみコンソールを表示する設定
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif
//メモリリーク検知
#if (_DEBUG)
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
		std::cout << errorcode << std::endl;
	}
	//Main Loop
	while (engine->SystemUpdate())
	{

	}
	//Delete Engine
	delete engine;
}