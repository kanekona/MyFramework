#include "StartScene.h"
#include "WinConfig.h"
#include "Engine\Framework.h"
StartScene::StartScene()
{
	tag = "StartScene";	
}
StartScene::~StartScene()
{

}
void StartScene::Entry()
{
	SetEntity(new WinConfig());
}