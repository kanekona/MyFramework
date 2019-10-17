#include "InputTest.h"
#include "Input\Input.h"
#include "System\System.h"

void InputTest::Update()
{
#if DEBUG_ENABLE
	CInput::Get()->DebugLog();
#endif
}

void InputTest::Entry()
{
}

InputTest::InputTest()
{
	KL::ClassFromName<InputTest>(&tag);
	std::cout << tag << std::endl;
	input = CInput::Get();
}

InputTest::~InputTest()
{
}
