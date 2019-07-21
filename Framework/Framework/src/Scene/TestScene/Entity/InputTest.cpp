#include "InputTest.h"
#include "Input\Input.h"
#include "System\System.h"

void InputTest::Update()
{
#if DEBUG_ENABLE
	Input::Get()->DebugLog();
#endif
}

void InputTest::Enter()
{
}

InputTest::InputTest()
{
	KL::ClassFromName<InputTest>(&tag);
	std::cout << tag << std::endl;
	input = Input::Get();
}

InputTest::~InputTest()
{
}
