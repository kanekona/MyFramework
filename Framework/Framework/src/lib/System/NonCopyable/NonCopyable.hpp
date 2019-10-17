#pragma once
/**
*@brief	コピーを禁止するclass
*
*このclassを継承したclassはコピーコンストラクタと代入演算を禁止されます
*/
class CNonCopyable
{
	void operator=(const CNonCopyable&) = delete;
	CNonCopyable(const CNonCopyable&) = delete;
protected:
	explicit CNonCopyable()
	{

	}
	virtual ~CNonCopyable()
	{

	}
};