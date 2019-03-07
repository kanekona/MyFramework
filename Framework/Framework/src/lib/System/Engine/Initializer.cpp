#include "Initializer.h"
#include "Event\Event.h"
#include "WinConfig\StartScene.h"
WindowParameter Initializer::ConfigWindow()
{
	return WindowParameter(Vec2Int(0, 30), Vec2Int(960, 540), "WindowName", false);
}
Scene* Initializer::SceneAdaptation()
{
	return new StartScene();
}