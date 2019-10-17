#include "Initializer.h"
#include "Event\Event.h"
#include "WinConfig\StartScene.h"
#include "Scene\Scene.h"
CWindowParameter CInitializer::ConfigWindow()
{
	return CWindowParameter(CVec2Int(0, 30), CVec2Int(540, 270), "WindowName", false);
}
CScene* CInitializer::SceneAdaptation()
{
	return new StartScene();
}