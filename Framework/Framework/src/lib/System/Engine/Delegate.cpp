#include "Delegate.h"

void CDelegate::AddFunc(const std::function<void()>& f)
{	
	s_func = f;
}

void CDelegate::Execution()
{
	s_func();
}

void CMultiDelegate::Run()
{
	for (auto&it : Delegates)
	{
		it.Execution();
	}
}

void CMultiDelegate::Reset()
{
	Delegates.clear();
}

void CMultiDelegate::Add(const CDelegate & InDelegate)
{
	Delegates.emplace_back(InDelegate);
}

CMultiDelegate::~CMultiDelegate()
{
	Reset();
}
