#pragma once
#include "Entity\Entity.h"
#include "Audio\Sound.h"
#include "Timer\glTimer.h"
class TestEntity : public CEntity
{
	void Update() override;
	void Entry() override;
public:
	explicit TestEntity();
	virtual ~TestEntity();
};