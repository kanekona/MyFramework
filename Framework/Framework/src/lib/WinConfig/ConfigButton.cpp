#include "ConfigButton.h"
#include "Input\Input.h"
#include "Event\WindowEvent\WindowEvent.h"
#include "Engine\Framework.h"
#include "StartScene.h"
#include "Scene\TestScene\TestScene.h"
ConfigButton::ConfigButton(const Transform& transform,const bool enableFullscreen)
	:Button(transform)
{
	enable = enableFullscreen;
}
ConfigButton::~ConfigButton()
{

}
void ConfigButton::Decision()
{
	int x, y;
	std::ifstream ifs("./data/event/windowSize.og");
	WindowEvent(ifs, &x, &y);
	Framework::Get()->GetWindow()->ChangeMode(0, 30, x, y, "WindowName", enable);
	Framework::Get()->ChangeScene(new TestScene());
}