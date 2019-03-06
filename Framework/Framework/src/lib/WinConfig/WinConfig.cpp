#include "WinConfig.h"
#include "Engine\Framework.h"
#include "Button\Button.h"
WinConfig::WinConfig()
{
	this->tag = "WinConfig";
}
WinConfig::~WinConfig()
{

}
void WinConfig::Enter()
{
	for (int i = 0; i < 2; ++i)
	{
		Button* button = new Button(Transform(Vec2(128 * i + (128 / 2) + (i * 30 + 30), 64 / 2 + 30), Vec2(128, 64)));
		Framework::Get()->GetScene()->SetEntity(button);
	}
}