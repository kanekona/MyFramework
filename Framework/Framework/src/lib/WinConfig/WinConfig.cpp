#include "WinConfig.h"
#include "Engine\Framework.h"
#include "ConfigButton.h"
WinConfig::WinConfig()
{
	tag = "WinConfig";
}
WinConfig::~WinConfig()
{
}
void WinConfig::Entry()
{
	CButton* button1 = new ConfigButton(CTransform(CFramework::Get()->GetPosition(4, 2, 5), CFramework::Get()->GetSize(2, 1)), true);
	button1->GetFont()->SetSize(64);
	button1->GetFont()->SetText(L"Yes");
	SetChildren(button1);
	CButton* button2 = new ConfigButton(CTransform(CFramework::Get()->GetPosition(4, 2, 7), CFramework::Get()->GetSize(2, 1)), false);
	button2->GetFont()->SetSize(64);
	button2->GetFont()->SetText(L"No");
	SetChildren(button2);
}
void WinConfig::Update()
{
}