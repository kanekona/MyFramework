#pragma once
#include "Entity\Entity.h"

class TextureTestEntity : public Entity
{
	void Update() override;
	void Enter() override;
public:
	explicit TextureTestEntity();
	virtual ~TextureTestEntity();
};