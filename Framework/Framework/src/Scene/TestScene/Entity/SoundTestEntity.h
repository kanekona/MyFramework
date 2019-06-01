#pragma once
#include "Entity\Entity.h"
#include "Audio\Sound.h"

class SoundTestEntity : public Entity
{
	Sound sound;
	float angle;
	void Enter() override;
	void Update() override;
	void ChangePosition();
	void ChangeVelocity();
	void ChangeDirection();
	void DebugCout();
	void Rotation();
public:
	explicit SoundTestEntity();
	virtual ~SoundTestEntity();
};