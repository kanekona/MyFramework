#include "InputTest.h"
#include "Input\Input.h"

void InputTest::Update()
{
}

void InputTest::Enter()
{
}

InputTest::InputTest()
{
	tag = typeid(this).name();
	std::cout << tag << std::endl;
	input = Input::Get();
}

InputTest::~InputTest()
{
}
