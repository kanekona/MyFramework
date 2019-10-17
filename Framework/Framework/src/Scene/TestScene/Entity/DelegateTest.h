#pragma once
#include "Entity\Entity.h"
#include "Engine\Delegate.h"
#include "StrID\StrID.h"

class DelegateTest : public CEntity
{
	CMultiDelegate DM;
	void Update() override;
	void Entry() override;
	void Test();
	static void S_Test();
public:
	explicit DelegateTest();
	virtual ~DelegateTest();
};