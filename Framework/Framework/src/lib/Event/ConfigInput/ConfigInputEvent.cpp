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
		//'/'‚ª“ª‚É‚Â‚¢‚Ä‚¢‚é‚à‚Ì‚Í“Ç‚Ýž‚Ü‚È‚¢
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
