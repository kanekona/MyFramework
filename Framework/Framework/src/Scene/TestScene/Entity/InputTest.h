#pragma once
#include "Entity\Entity.h"

class CInput;

class InputTest : public CEntity
{
	CInput* input;
	void Update() override;
	void Entry() override;
public:
	explicit InputTest();
	virtual ~InputTest();
};