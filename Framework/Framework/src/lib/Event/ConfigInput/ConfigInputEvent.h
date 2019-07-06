#pragma once
#include <fstream>
#include <sstream>

class ConfigInputEvent
{
	void ChangeInputConfig(std::string& text);
public:
	explicit ConfigInputEvent(std::ifstream& ifs);
	virtual ~ConfigInputEvent();
};