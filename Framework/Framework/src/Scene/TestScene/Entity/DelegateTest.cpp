#include "DelegateTest.h"

void DelegateTest::Update()
{
	DM.Run();
}

void DelegateTest::Entry()
{
	CDelegate add;
	add.AddFunc(std::bind(&DelegateTest::Test, this));
	CDelegate s_add;
	s_add.AddFunc(std::bind(&DelegateTest::S_Test));
	DM.Add(add);
	DM.Add(s_add);
}

void DelegateTest::Test()
{
	printf("Test\n");
}

void DelegateTest::S_Test()
{
	printf("S_Test\n");
}

DelegateTest::DelegateTest()
{
}

DelegateTest::~DelegateTest()
{
}
