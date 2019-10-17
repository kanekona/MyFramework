#include "ConfigButton.h"
#include "Input\Input.h"
#include "Event\WindowEvent\WindowEvent.h"
#include "Engine\Framework.h"
#include "StartScene.h"
#include "Scene\TestScene\TestScene.h"
#include "Window\Window.h"
ConfigButton::ConfigButton(const CTransform& transform,const bool enableFullscreen)
	:CButton(transform)
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
	CWindowEvent(ifs, &x, &y);
	CFramework::Get()->GetWindow()->ChangeMode(0, 30, x, y, "WindowName", enable);
	CFramework::Get()->ChangeScene(new TestScene());
}