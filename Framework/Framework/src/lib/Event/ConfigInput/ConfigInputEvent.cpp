#include "ConfigInputEvent.h"
#include "Input\Input.h"
#include "System\System.h"
void CConfigInputEvent::ChangeInputConfig(std::string& text)
{
	KL::Trim(&text, " ");
	std::string first;
	std::string second;
	KL::Split(text, "=", &first, &second);
	CStrID Key(first);
	int keyNumber;
	KL::StringFromNumber(second, &keyNumber);
	CInput::Get()->SetPadConfig(Key, keyNumber);
}

CConfigInputEvent::CConfigInputEvent(std::ifstream& ifs)
{
	std::string lineText;
	while (std::getline(ifs, lineText))
	{
		//'/'‚ª“ª‚É‚Â‚¢‚Ä‚¢‚é‚à‚Ì‚Í“Ç‚Ýž‚Ü‚È‚¢
		if (lineText.at(0) == '/')
		{
			continue;
		}
		ChangeInputConfig(lineText);
	}
	CInput::Get()->RegisterPadConfig();
}

CConfigInputEvent::~CConfigInputEvent()
{
}
