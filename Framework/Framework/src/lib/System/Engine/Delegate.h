#pragma once
#include <vector>
#include <functional>

class CDelegate;
class CMultiDelegate;

class CDelegate
{
	std::function<void()> s_func;
public:
	void AddFunc(const std::function<void()>& f);
	void Execution();
};

class CMultiDelegate
{
	std::vector<CDelegate> Delegates;
public:
	void Run();
	void Reset();
	void Add(const CDelegate& InDelegate);
	virtual ~CMultiDelegate();
};