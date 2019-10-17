#pragma once
#include "Entity\Entity.h"
#include "Audio\Sound.h"

class SoundTestEntity : public CEntity
{
	CSound sound;
	float angle;
	void Entry() override;
	void Update() override;
	void ChangePosition();
	void ChangeVelocity();
	void ChangeDirection();
	void DebugCout();
	void Rotation();
	void UpdateReferenceDistance();
public:
	explicit SoundTestEntity();
	virtual ~SoundTestEntity();
};