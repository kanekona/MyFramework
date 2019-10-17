#pragma once
#include <fstream>
#include <sstream>

class CConfigInputEvent
{
	void ChangeInputConfig(std::string& text);
public:
	explicit CConfigInputEvent(std::ifstream& ifs);
	virtual ~CConfigInputEvent();
};