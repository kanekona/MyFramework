#pragma once
#include "Entity\Entity.h"

class Input;

class InputTest : public Entity
{
	Input* input;
	void Update() override;
	void Enter() override;
public:
	explicit InputTest();
	virtual ~InputTest();
};