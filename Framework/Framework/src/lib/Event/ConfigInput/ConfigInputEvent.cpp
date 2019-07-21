#include "ConfigInputEvent.h"
#include "Input\Input.h"
#include "System\System.h"
void ConfigInputEvent::ChangeInputConfig(std::string& text)
{
	KL::Trim(&text, " ");
	std::string first;
	std::string second;
	KL::Split(text, "=", &first, &second);
	StrID Key(first);
	int keyNumber;
	KL::StringFromNumber(second, &keyNumber);
	Input::Get()->SetPadConfig(Key, keyNumber);
}

ConfigInputEvent::ConfigInputEvent(std::ifstream& ifs)
{
	std::string lineText;
	while (std::getline(ifs, lineText))
	{
		//'/'が頭についているものは読み込まない
		if (lineText.at(0) == '/')
		{
			continue;
		}
		ChangeInputConfig(lineText);
	}
	Input::Get()->RegisterPadConfig();
}

ConfigInputEvent::~ConfigInputEvent()
{
}
