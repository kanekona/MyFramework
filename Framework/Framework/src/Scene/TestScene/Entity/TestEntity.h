#pragma once
#include "Entity\Entity.h"
#include "Audio\Sound.h"
class TestEntity : public Entity
{
	void Update() override;
	void Enter() override;
public:
	explicit TestEntity();
	virtual ~TestEntity();
};